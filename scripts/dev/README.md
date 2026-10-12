# 源码增量维护

日常直接编辑源码。明确修改完成后运行 `python3 scripts/dev/record-part55-deltas.py`，审阅 docs/project/part55-deltas.json 再运行构建/检查；不能用更新清单掩盖未经授权修改。该工具从 pre-part5-5-implementation 登记实际变化，不自动执行任何GUI。一次性实施工具已移出工程，不作为第二套权威源码。
