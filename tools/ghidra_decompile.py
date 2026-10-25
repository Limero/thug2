#!/usr/bin/env python3
"""Decompile GameCube PPC functions via Ghidra headless (flatpak).

Wraps the flatpak Ghidra's analyzeHeadless to decompile one or more
functions from build/G2TE52/main.elf (or orig DOL) and print C.

Flatpak Ghidra ships as org.ghidra_sre.Ghidra with a read-only
launch.properties symlink -> /var/config/ghidra.properties that fails
outside the sandbox. This tool works around it by copying
files/lib/ghidra/support to a temp dir with a real launch.properties
(and a Ghidra symlink) and running with the flatpak's bundled JDK,
so /tmp wipe does not break it.

Usage:
  tools/venv/bin/python tools/ghidra_decompile.py 0x8026EAAC
  tools/venv/bin/python tools/ghidra_decompile.py 0x8026EAAC 0x8026FD2C --out-dir /tmp/ghidra_out
  tools/venv/bin/python tools/ghidra_decompile.py 0x8008076C --elf orig/G2TE52/sys/main.dol --no-analysis  # raw

Output is written to stdout (single addr) or to /tmp/ghidra_<addr>.c
(batch) and also printed. The tool does not affect the build (inert).

Requires: flatpak Ghidra installed (org.ghidra_sre.Ghidra), ~2G RAM, ~70s
for first analysis (ELF import). Subsequent decompiles in same invocation
are fast (one headless run).

See also: tools/disasm.py (capstone), tools/ps_disasm.py (PS-aware),
          docs/parkings/44-math-entry-staging-homing-wall.md (example where
          Ghidra helped for fdlibm log vs tanh).
"""
import argparse
import glob
import os
import shutil
import subprocess
import sys
import tempfile
import textwrap

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Java script that dumps one or more functions
DUMP_BATCH_JAVA = textwrap.dedent("""\
    // Dump batch - decompile each addr to /tmp/ghidra_<hex>.c
    import ghidra.app.decompiler.*;
    import ghidra.app.script.GhidraScript;
    import ghidra.program.model.address.*;
    import ghidra.program.model.listing.*;

    public class DumpBatch extends GhidraScript {
        @Override
        protected void run() throws Exception {
            if (getScriptArgs().length == 0) {
                println("Usage: DumpBatch <hexaddr>...");
                return;
            }
            DecompInterface decomp = new DecompInterface();
            decomp.openProgram(currentProgram);
            for (String addrStr : getScriptArgs()) {
                try {
                    Address addr = toAddr(addrStr);
                    Function func = getFunctionAt(addr);
                    if (func == null) func = getFunctionContaining(addr);
                    if (func == null) {
                        println("No function at " + addrStr);
                        continue;
                    }
                    println("=== " + func.getName() + " " + func.getEntryPoint() + " ===");
                    DecompileResults res = decomp.decompileFunction(func, 30, monitor);
                    if (!res.decompileCompleted()) {
                        println("Failed: " + res.getErrorMessage());
                        continue;
                    }
                    String code = res.getDecompiledFunction().getC();
                    String out = "/tmp/ghidra_" + addrStr.replace("0x","").replace("0X","") + ".c";
                    java.io.PrintWriter pw = new java.io.PrintWriter(out);
                    pw.println("// " + func.getName() + " " + func.getEntryPoint());
                    pw.println(code);
                    pw.close();
                    println("Wrote " + out);
                    // also print truncated to log
                    println(code.substring(0, Math.min(2000, code.length())));
                } catch (Exception e) {
                    println("Error for " + addrStr + ": " + e);
                    e.printStackTrace();
                }
            }
            decomp.dispose();
        }
    }
    """)

DUMP_ONE_JAVA = textwrap.dedent("""\
    // Dump one function
    import ghidra.app.decompiler.*;
    import ghidra.app.script.GhidraScript;
    import ghidra.program.model.address.*;
    import ghidra.program.model.listing.*;

    public class DumpOne extends GhidraScript {
        @Override
        protected void run() throws Exception {
            if (getScriptArgs().length == 0) {
                println("Usage: DumpOne <hexaddr> [outFile]");
                return;
            }
            String addrStr = getScriptArgs()[0];
            String outFile = getScriptArgs().length > 1 ? getScriptArgs()[1] : null;
            Address addr = toAddr(addrStr);
            Function func = getFunctionAt(addr);
            if (func == null) func = getFunctionContaining(addr);
            if (func == null) {
                println("No function at " + addrStr);
                return;
            }
            println("Decompiling " + func.getName() + " at " + func.getEntryPoint());
            DecompInterface decomp = new DecompInterface();
            decomp.openProgram(currentProgram);
            DecompileResults res = decomp.decompileFunction(func, 30, monitor);
            if (!res.decompileCompleted()) {
                println("Decompile failed: " + res.getErrorMessage());
                decomp.dispose();
                return;
            }
            String code = res.getDecompiledFunction().getC();
            println(code);
            if (outFile != null) {
                java.io.PrintWriter pw = new java.io.PrintWriter(outFile);
                pw.println(code);
                pw.close();
                println("Wrote to " + outFile);
            }
            decomp.dispose();
        }
    }
    """)


def find_ghidra():
    """Return (ghidra_lib_dir, jdk_bin) or (None, None)."""
    home = os.path.expanduser("~")
    candidates = glob.glob("/var/lib/flatpak/app/org.ghidra_sre.Ghidra/x86_64/stable/*/files/lib/ghidra")
    if not candidates:
        # also check user flatpak install (under the caller's $HOME,
        # not a hardcoded home-directory path)
        candidates = glob.glob(os.path.join(
            home, ".local/share/flatpak/app/org.ghidra_sre.Ghidra/x86_64/stable/*/files/lib/ghidra"))
        # fallback: try find via flatpak exports
        candidates = glob.glob("/var/lib/flatpak/app/org.ghidra_sre.Ghidra/*/files/lib/ghidra")
    for c in candidates:
        jdk = os.path.join(os.path.dirname(os.path.dirname(c)), "jdk", "bin", "java")
        # c is .../files/lib/ghidra, jdk is .../files/jdk/bin/java
        jdk_bin = os.path.join(os.path.dirname(c), "..", "jdk", "bin", "java")
        jdk_bin = os.path.normpath(jdk_bin)
        if os.path.isfile(jdk_bin) and os.path.isfile(os.path.join(c, "support", "analyzeHeadless")):
            return c, os.path.dirname(jdk_bin)
    # try via flatpak list path
    for root in glob.glob("/var/lib/flatpak/app/org.ghidra_sre.Ghidra/x86_64/stable/*/files"):
        ghidra = os.path.join(root, "lib", "ghidra")
        jdk_bin = os.path.join(root, "jdk", "bin")
        if os.path.isdir(ghidra) and os.path.isfile(os.path.join(jdk_bin, "java")):
            return ghidra, jdk_bin
    return None, None


def prepare_headless(ghidra_lib, jdk_bin):
    """Create a temp copy of support/ with a real launch.properties.

    Returns (headless_path, tmp_root) where headless_path is the
    analyzeHeadless to run. Caller must clean tmp_root.
    """
    tmp_root = tempfile.mkdtemp(prefix="ghidra_headless_")
    # support dir with fixed launch.properties
    src_support = os.path.join(ghidra_lib, "support")
    dst_support = os.path.join(tmp_root, "support")
    # launch.properties is a dangling symlink -> /var/config/ghidra.properties outside sandbox;
    # copytree with symlinks=False would try to follow it and fail, so ignore dangling.
    shutil.copytree(src_support, dst_support, symlinks=False, ignore_dangling_symlinks=True)
    # fix dangling symlink launch.properties -> /var/config/ghidra.properties
    dst_prop = os.path.join(dst_support, "launch.properties")
    if os.path.islink(dst_prop) or not os.path.isfile(dst_prop):
        # remove symlink if exists (may be dangling and thus not copied, so not present)
        try:
            os.remove(dst_prop)
        except FileNotFoundError:
            pass
        src_orig = os.path.join(src_support, "launch.properties.orig")
        if os.path.isfile(src_orig):
            shutil.copy2(src_orig, dst_prop)
        else:
            # fallback: create minimal
            open(dst_prop, "w").write("# minimal launch.properties\n")
    # need Ghidra dir symlink for INSTALL_DIR/Ghidra lookup
    dst_ghidra_link = os.path.join(tmp_root, "Ghidra")
    src_ghidra = os.path.join(ghidra_lib, "Ghidra")
    if not os.path.exists(dst_ghidra_link):
        os.symlink(src_ghidra, dst_ghidra_link)
    headless = os.path.join(dst_support, "analyzeHeadless")
    os.chmod(headless, 0o755)
    # also ensure launch.sh is executable
    try:
        os.chmod(os.path.join(dst_support, "launch.sh"), 0o755)
    except FileNotFoundError:
        pass
    return headless, tmp_root


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addrs", nargs="+", help="hex addresses, e.g. 0x8026EAAC")
    ap.add_argument("--elf", default="build/G2TE52/main.elf", help="ELF/DOL to import (default: build/G2TE52/main.elf)")
    ap.add_argument("--out-dir", default="/tmp", help="where to write /tmp/ghidra_*.c (default: /tmp)")
    ap.add_argument("--project-dir", default=None, help="temp project dir (default: mktemp)")
    ap.add_argument("--no-analysis", action="store_true", help="skip auto-analysis (functions not found)")
    ap.add_argument("--timeout", type=int, default=180, help="headless timeout seconds (default: 180)")
    ap.add_argument("--keep-project", action="store_true", help="do not delete temp project")
    args = ap.parse_args()

    # normalize addrs
    norm_addrs = []
    for a in args.addrs:
        a = a.strip()
        if not a.lower().startswith("0x"):
            a = "0x" + a
        # validate
        try:
            int(a, 16)
        except ValueError:
            print(f"Invalid address: {a}", file=sys.stderr)
            sys.exit(1)
        norm_addrs.append(a)

    ghidra_lib, jdk_bin = find_ghidra()
    if not ghidra_lib:
        print("Ghidra flatpak not found at /var/lib/flatpak/app/org.ghidra_sre.Ghidra", file=sys.stderr)
        print("Install: flatpak install flathub org.ghidra_sre.Ghidra", file=sys.stderr)
        sys.exit(1)
    if not os.path.isfile(args.elf):
        # fallback to orig DOL
        alt = "orig/G2TE52/sys/main.dol"
        if os.path.isfile(alt):
            print(f"ELF {args.elf} not found, falling back to {alt}", file=sys.stderr)
            args.elf = alt
        else:
            print(f"ELF not found: {args.elf}", file=sys.stderr)
            sys.exit(1)

    # prepare headless wrapper with fixed launch.properties
    headless, tmp_root = prepare_headless(ghidra_lib, jdk_bin)
    # prepare scripts
    script_dir = tempfile.mkdtemp(prefix="ghidra_scripts_")
    try:
        # Use batch script for >1 addr, single for 1
        script_name = "DumpBatch.java" if len(norm_addrs) > 1 else "DumpOne.java"
        script_content = DUMP_BATCH_JAVA if len(norm_addrs) > 1 else DUMP_ONE_JAVA
        with open(os.path.join(script_dir, script_name), "w") as f:
            f.write(script_content)

        proj_dir = args.project_dir or tempfile.mkdtemp(prefix="ghidra_proj_")
        proj_name = "THUG2"
        # ensure paths are absolute
        elf_abs = os.path.abspath(args.elf)
        script_path = script_dir

        # build analyzeHeadless command
        # Use PowerPC:BE:32:default (GameCube Gekko is default with Altivec)
        # For DOL fallback, the loader will be Raw Binary; ELF is preferred.
        cmd = [
            headless,
            proj_dir, proj_name,
            "-import", elf_abs,
            "-processor", "PowerPC:BE:32:default",
            "-cspec", "default",
            "-scriptPath", script_path,
        ]
        if args.no_analysis:
            cmd.append("-noanalysis")
        # postScript args: DumpBatch addrs OR DumpOne addr outFile
        if len(norm_addrs) > 1:
            cmd += ["-postScript", "DumpBatch.java"] + norm_addrs
        else:
            out_file = os.path.join(args.out_dir, f"ghidra_{norm_addrs[0].replace('0x','')}.c")
            cmd += ["-postScript", "DumpOne.java", norm_addrs[0], out_file]

        cmd += ["-deleteProject"]

        env = dict(os.environ)
        env["PATH"] = jdk_bin + ":" + env.get("PATH", "")
        # ensure XDG_RUNTIME_DIR exists for flatpak workaround if needed
        if not env.get("XDG_RUNTIME_DIR"):
            # headless doesn't need it now that we bypass flatpak, but set to tmp
            env["XDG_RUNTIME_DIR"] = "/tmp"

        print(f"Ghidra: {ghidra_lib}", file=sys.stderr)
        print(f"JDK: {jdk_bin}", file=sys.stderr)
        print(f"ELF: {elf_abs}", file=sys.stderr)
        print(f"Project: {proj_dir}/{proj_name}", file=sys.stderr)
        print(f"Script: {script_name} {norm_addrs}", file=sys.stderr)
        print(f"Headless: {' '.join(cmd)}", file=sys.stderr)
        print("--- Ghidra log (tail) ---", file=sys.stderr)

        # run with timeout
        try:
            proc = subprocess.run(cmd, env=env, timeout=args.timeout, capture_output=False)
            rc = proc.returncode
        except subprocess.TimeoutExpired:
            print(f"Timeout after {args.timeout}s (analysis of 5.5M ELF takes ~70s)", file=sys.stderr)
            rc = 124

        # after run, collect outputs
        if len(norm_addrs) > 1:
            for a in norm_addrs:
                out = f"/tmp/ghidra_{a.replace('0x','')}.c"
                if os.path.isfile(out):
                    print(f"\n=== {a} -> {out} ===", file=sys.stderr)
                    # cat to stdout for convenience
                    with open(out) as f:
                        data = f.read()
                        print(data[:8000])
                        if len(data) > 8000:
                            print(f"\n... truncated, full at {out} ({len(data)} bytes)", file=sys.stderr)
                else:
                    print(f"No output for {a} (expected {out})", file=sys.stderr)
        else:
            out = os.path.join(args.out_dir, f"ghidra_{norm_addrs[0].replace('0x','')}.c")
            if os.path.isfile(out):
                print(f"\nWrote {out}", file=sys.stderr)
                with open(out) as f:
                    print(f.read()[:8000])
            else:
                print(f"No output file {out}, check log", file=sys.stderr)

        sys.exit(rc if isinstance(rc, int) else 0)
    finally:
        # cleanup temp dirs (keep out files in /tmp)
        shutil.rmtree(tmp_root, ignore_errors=True)
        shutil.rmtree(script_dir, ignore_errors=True)
        if not args.keep_project and args.project_dir is None:
            # proj_dir was mktemp, remove
            try:
                shutil.rmtree(proj_dir, ignore_errors=True)
            except NameError:
                pass


if __name__ == "__main__":
    main()
