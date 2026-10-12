# 武斗镇恢复档 — 2026-10-07 / Codex

用户个人档损坏，明确使用手机MyBoy。按当前修复工程重建刚到武斗镇的普通卡带存档，通过游戏原生菜单实际保存；不是修复原个人档，也不是从头自然游玩。无GUI；延续当前故障恢复任务的运行验证授权。没有更改游戏源码、设计Canon或既有ROM。

交付：D:/Pokemon gba/artifacts/MyBoy-Dewford-Recovery-2026-10-07.zip（ROM + 同名普通.sav + 使用说明 + verification.json），解压目录artifacts/myboy-dewford-2026-10-07/。主角男/PLAYER；岩石徽章1、沼跃鱼18（无碎岩）、蛇纹熊11、正常拉鲁拉丝蛋（SpA31，孵化Lv1）；学习装置开，3500元及基础补给。博士/满充/首次劲敌/首馆/森林和卡绿水舰队/社长/领航员/哈奇航船前置已按现有脚本恢复；藤树、大吾送信、凯那与多数可选支线未做，不发后期能力。信件与得文包裹仍在包，哈奇在码头。原个人姓名/训练家ID/收藏/支线无法还原。

.sav为131072字节，14有效扇区CRC式原生加和校验PASS，普通读档SAVE_STATUS_OK。原生读取确认3队员/等级/非坏蛋/蛋SpA31/沼跃鱼4技能/任务道具与货币。当前release搭配新save的续档、图鉴后新种捕获、队伍空位、满队+蛋+经验、已拥有种类捕获5场景PASS；输入save未修改。完整通用夹具后来的一轮KO输入停在battleOutcome0，未标通过、未宣称全部7例PASS；此恢复任务仅主张已完成5例，ROM本身的既有KO回归结果见原Bug报告。手机MyBoy未实测，导入位置依版本；官方FAQ确认新版为应用私有目录并建议关闭损坏的Quick load on start。不得将mGBA测试成功说成手机已导入成功。

ROM SHA256：2f82ad52ca710347ff2ef46531d31811ed24cbf13c2b2e6c14d5a1d25d8715da
SAVE SHA256：a31bda7cd0343d05ed805ed0bdf021a0d35b13e774cae6d67bceeba9ae4cec2c

制作脚本、配置、日志、native检查与截图在交付解压目录evidence/；完整运行工作目录为WSL /home/pokemon/qa-bugfix-2026-10-07/recovery-save。仅给无界面运行工具增加指针相对写入/调用命令，未改游戏引擎。不覆盖原个人/当前默认.sav，不改剧情状态机。后续默认禁GUI/ROM规则仍保留，美术仍暂停。
