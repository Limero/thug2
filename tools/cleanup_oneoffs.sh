#!/usr/bin/env bash
# Delete throwaway one-off debug tools. Run from repo root: bash tools/cleanup_oneoffs.sh
set -u
cd "$(dirname "$0")/.."

# --- explicit one-off lists ---
rm -f \
  tools/dbg_*.py tools/dbg_*.sh \
  tools/check31.py tools/check31b.py tools/check_last2.py tools/check_last2b.py \
  tools/check_leaf.py tools/check_proto.py \
  tools/definitive31.py tools/diff31.py \
  tools/dump_fail4.py tools/dump_fail5.py tools/dump_fail5b.py tools/dump_fail5c.py \
  tools/dump_fails10.py \
  tools/err_ctx5.py tools/fail_lines5.py tools/final_test.py tools/find_unk3.py \
  tools/inspect7.py tools/inspect7b.py tools/inspect_fail4.py tools/iso31.py \
  tools/leaf68.py tools/leafcompile5.sh tools/leafdecl5.py tools/leaferr7.py \
  tools/leafhead5.py tools/log_limits.py tools/log_steps.py \
  tools/measure_impact.py tools/min_proto_test.sh \
  tools/perstep.py \
  tools/raw_check2.py tools/rawdump3.py tools/rawdump_fail4.py tools/rawerr5.py \
  tools/rawerr_fail4.py tools/rawproto5.py \
  tools/re_check5.py tools/re_dbg5.py tools/re_scan5.py \
  tools/settle31.py tools/shapes_fail4.py tools/show_chunks.py \
  tools/test394.py tools/test_fcd.py tools/test_fpf.py \
  tools/test_bg.py tools/test_c32.py tools/test_fams.py tools/test_fn_13F6.py \
  tools/test_fn_13F6b.py tools/test_last3.py tools/test_lg.py tools/test_lg2.py \
  tools/test_mr9.py tools/test_mr9b.py tools/test_mw_masks.py tools/test_mw_masks2.py \
  tools/test_newpats.py tools/test_rl.py tools/test_rl2.py tools/test_rl8.py \
  tools/test_rl8b.py tools/test_spr.py tools/test_stragglers.py tools/test_tramp.py \
  tools/test_vcall_b.py tools/test_vcall_c.py \
  tools/unit_fail.py tools/unit_fail2.py tools/unit_split.py \
  tools/verify5b.py tools/verify5c.py tools/verify_split.py \
  tools/wipcheck5.py tools/body7.py tools/body7b.py tools/body7c.py \
  tools/bucket_all_fail.py tools/bucket_fail4.py \
  tools/scan_crclr.py tools/scan_h.py tools/scan_leaves.py tools/scan_leaves2.py \
  tools/sample_groups.py tools/sample_groups2.py \
  tools/try_c.py \
  tools/park_tramps.py tools/park_tramps2.py tools/park_5254C.py \
  tools/commit4.sh tools/commit5.sh tools/finish3.sh \
  tools/rebuild_after_park.sh tools/rerun_split.sh tools/verify_state.sh \
  tools/progress_and_survey.sh \
  tools/find_blrl_fns.py \
  tools/survey_sda.py tools/survey_shapes.py tools/survey_sig.py \
  tools/survey_small.py tools/survey_wrappers.py tools/survey_wrappers2.py \
  tools/fix_sw*.py tools/variant_sw*.py tools/promote_sw*.py tools/test_batch*.py \
  tools/ab_raw_lit.py tools/fix_raw_lit.py tools/fix_fnptr_calls.py \
  tools/score_addrs.py tools/promo_one.py tools/gen_dispatch42.py \
  tools/harvest_crclr2.py tools/fix_harvest_headers.py

echo "=== remaining tools ==="
ls tools/*.py tools/*.sh 2>/dev/null | wc -l
echo "=== sanity: every doc-referenced tool still present? ==="
missing=0
for t in add_gen_dispatch.py add_gen_leaves.py add_gen_vcall.py bisect_rules.py \
         bucket_fail5.py changes_fmt.py classify_fns.py cmp_dols.py cold_rebuild.sh \
         disasm.py dolphin-cli.sh fill_wip_drafts.py final_verify.sh find_int_fns.py \
         find_more_blrl.py fix_rodata.py gen_dispatch_fns.py gen_leaves.py \
         gen_progress.py rename_script_cmds.py rename_vtable_methods.py apply_wip_names.py gen_qb_constants.py apply_qb_constants.py resolve_qb_hashes.py analyze_data_structures.py gen_vcall_fns.py gen_wip_drafts.py iso_chunk31.py \
         objdiff_rng.sh patch_dol.py project.py promote_wip.py register_build.sh \
         replace_dol.py scan_frames.py scan_gpr_frames.py scan_pun.py \
         survey_leaves_missed.py test_wip_drafts.py trace_rules.py verify36.py \
         verify5.py wip.py decompctx.py download_tool.py ninja_syntax.py \
         transform_dep.py preserve_tmp.sh sweep3.sh promote3.sh \
         score_body.py which_words.py fix_call_arity.py fix_void_calls.py \
         store_order_search.py stmt_perm_search.py proto_audit.py gen_str_data.py \
         gen_data.py pad_sdk_data.py gen_vtable.py sda_verify.py flagdiff.py ps_diff.py ps_disasm.py; do
  if [ ! -e "tools/$t" ]; then echo "  MISSING: tools/$t"; missing=1; fi
done
[ "$missing" = 0 ] && echo "  all doc-referenced tools present"
