[33mcommit f91d901b3c17fd8dcb12dbbe407ed78099ae4962[m[33m ([m[1;36mHEAD -> [m[1;32mmaster[m[33m)[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Dec 15 14:40:55 2020 +0000

    added atm robbery

[33mcommit 0881cdc0bc70628f81664b3df3ef159c55f1dd54[m[33m ([m[1;31morigin/master[m[33m, [m[1;31morigin/HEAD[m[33m)[m
Author: PatrickGTR <patricksubang@live.com>
Date:   Fri Dec 11 15:10:56 2020 +0000

    fix center alignment

[33mcommit 52aaa81aeaae9c18a749777112e76580ebbda9fa[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Dec 11 15:07:32 2020 +0000

    beautify readme.md, added logo & discord logo +redirect

[33mcommit b1c56759b61a1fa54ece638a576a6ff15a4f8502[m
Merge: 6140398 7e8f98a
Author: Patrick <pds2k12@live.com>
Date:   Fri Dec 11 14:47:47 2020 +0000

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 6140398cd4d4e2458901b22f17ea48523528d2f5[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Dec 11 14:46:56 2020 +0000

    Resize UI -> TD Menu

[33mcommit d33611720e8875d80e18cdc0856cdd584e6495af[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Dec 11 13:13:22 2020 +0000

    redirct /help -> /commands

[33mcommit f6e505f211cbd70c8c124564e00b286a054d5482[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Dec 11 13:00:56 2020 +0000

    add distance check on MMB cuff & arrest, detonate calls OnExplosiveDetonate

[33mcommit 7e8f98a47f75eeb32ec393770f67ef8fdbc4d3b8[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Dec 11 11:23:27 2020 +0800

    Update README.md

[33mcommit 0d2759dc25e0e1c680520e4faa6fcb0cead7be5d[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 10 23:07:23 2020 +0000

    added loadtime and total houses in houses modeul

[33mcommit 42e4da754c4a2339c18371b803bab7590669e744[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 10 22:56:10 2020 +0000

    player sometimes dies on first spawn, add a check if health loaded is not 0.

[33mcommit 53720afd1f6d88a4e90f41d003e502c7075526fe[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 10 22:13:17 2020 +0000

    fix skin saving bug, fix class selection bug (data not being resetted)

[33mcommit 8d9334c749b3bcfa5073f42f9da0335795058910[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Dec 8 15:24:22 2020 +0000

    fix bug where /furniture -> won't let you edit again once you close SelectObject, data not being initalised on command start.

[33mcommit ee50e9f4014ba4995cad6469e6acf0b9aa164693[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Dec 8 04:50:24 2020 +0000

    fix bug with /cuff, nearby crime, reset furniture data on connect, added garbage_collector side job, temporarily removed pawn-env

[33mcommit 72b8a1287138a7e47f7dfaf53dbcda81138678ec[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Dec 6 13:44:40 2020 +0000

    move side-jobs to systems/jobs, added sweeper side job

[33mcommit 0aaffff9afe4630bda217e6d9803f9ebb682b0c1[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Dec 4 02:06:54 2020 +0000

    added bomb dealer, added atm func getobjectid, getclosest, fix bugs in /gang and added /gangs

[33mcommit 2e0322671e036e983a1a0d619e357dc64fa49ecc[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 3 01:25:00 2020 +0000

    move player_weapons table setup to mysql_tquery_file

[33mcommit de072ee9b829df9e1969a4004853b5f0de46c969[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 3 01:22:28 2020 +0000

    move jail code to player_jail.inc

[33mcommit 7303fa08e62b87c8a8ac500880d48613e7360b0b[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 3 01:18:03 2020 +0000

    can't /cuff innocent players

[33mcommit a1711ba353e5c18a63422ac5adf98a0731e4ad4f[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 3 01:15:48 2020 +0000

    fix /goto, add late declaration of x, y, z in /goto and /get cmd

[33mcommit e23440c92b2b08dba292a8b3ccd46f461eb5028b[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Dec 3 01:13:12 2020 +0000

    fix # admin chat, disallow self arrest & self cuff

[33mcommit 9bcfbd90c2a7b515791e8dea166b0ba6ae90d794[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Dec 2 23:14:51 2020 +0000

    avoid direct calling commands, refactor cuff/arrest modules

[33mcommit 52d5f109d17eb7f1dcf58b1698993b728d4d0e0c[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Dec 2 14:16:03 2020 +0000

    refactor Player_InJail function, change format of robbery and SendAdminMsg, added punishment for cuffed player who leaves, punishment = (wanted-level * 2) * 2

[33mcommit a62037833f5e7706dfadb5b03a312c7fc20ea976[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Dec 2 02:02:10 2020 +0000

    updated pizza delivery mission, added murder crime, added Weapon_DeleteEntry

[33mcommit b0dc0c92086664cdea4f5338ecfcad03eeed598f[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Dec 1 14:56:33 2020 +0000

    ammunation refactored

[33mcommit d07baea0ab937d3f1008d539d2f6fc5d917eecdb[m
Merge: 4abf81d f7cf002
Author: Patrick <pds2k12@live.com>
Date:   Tue Dec 1 14:42:21 2020 +0000

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit f7cf002e52039e2bd6338c95fd84da90648e45b1[m
Merge: e705e23 e4c78e1
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Dec 1 14:42:10 2020 +0000

    Merge pull request #49 from PatrickGTR/acmds
    
    acmds revision

[33mcommit e4c78e1b8e7878bfdcedc2bf274fb804de6ad095[m[33m ([m[1;31morigin/acmds[m[33m)[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Dec 1 21:44:35 2020 +0800

    Deleted old system of admin commands

[33mcommit d4c246b9b491c9a528acca21aaa4a5fab9a3acab[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Dec 1 21:39:54 2020 +0800

    Admin commands

[33mcommit 4abf81db7c06b8553583f2063aa708e252ff7a14[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Dec 1 13:23:01 2020 +0000

    finale acmds

[33mcommit e705e230240b2e7d7fd3e7e1b45e0b580fbce3dc[m[33m ([m[1;31morigin/pullme[m[33m)[m
Merge: b45c2cd 49e7367
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon Nov 30 16:09:28 2020 +0800

    Merge pull request #47 from PatrickGTR/EnEx-Recreate
    
    Weapon Dealer remake

[33mcommit 49e7367c1c9bd0f2a7a5c5aaa60d336b968a7ffa[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Nov 27 12:16:27 2020 +0800

    changed player_weaponInv

[33mcommit cc59a2b8b1f77c6ce10978facf3776ca07aaf523[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Nov 27 12:15:21 2020 +0800

    Deleted SendAdminUsage in EnEx branch

[33mcommit b45c2cd5a7a7924a324813f123e6f8eb9d02987f[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Nov 27 02:48:30 2020 +0000

    fix # for admins, log admin commands (needs formatting)

[33mcommit 44131d825fd9144ca9ce37a460b28f00a1d271ba[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Nov 27 09:14:04 2020 +0800

    weapon dealer remake

[33mcommit d9f593527a66c2c4cb186a0684e116d8a16eb0d1[m
Merge: b3794ab ca3bf6c
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Nov 27 07:38:49 2020 +0800

    Merge branch 'master' into EnEx-Recreate

[33mcommit ca3bf6c6b5282c14fe219417d234f8de7bf2ae90[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Nov 26 22:57:36 2020 +0000

    fixed typo mysql_tquery -> mysql_tquery_file

[33mcommit b3794ab395f09a4841c162f6dcae2986aa6f8cc6[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Nov 27 05:19:00 2020 +0800

    remake job weapon-dealer

[33mcommit f054426bb2108a02da1e6c444bb868ea0dffb04a[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Nov 26 20:31:53 2020 +0000

    fixed old code when SETUP_TABLE is set to true

[33mcommit 5dac1eb92a8f7bf24d8521cbd9e1f9c5d4bbc23c[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Nov 26 20:17:13 2020 +0000

    added optional reason param for admin cmds, /settester optimize, fixed /freeze

[33mcommit e448d64009b3256c1709b7c0642bf5686c4fa96a[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Nov 26 19:41:20 2020 +0000

    added message for atm admin cmds

[33mcommit f58a42a39a9aa4e293e120a0bd19f3f7e324f9b5[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Nov 26 19:36:19 2020 +0000

    move spawn protection to MessageBox, better visual for ATM machines + labels

[33mcommit 722b1c40fa1ddaee04416e5f575797b83119185a[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Nov 26 18:33:40 2020 +0000

    added atms to tables.inc, table setu moved to atms.sql & add # for admin chat

[33mcommit 0f4bc0597c4d10dc11ce385009733fa855092fd4[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Nov 25 14:45:01 2020 +0000

    add admin_cmd_* module, refactor/clean up admin cmds

[33mcommit 12a9f8d28817c5c2b289b921cd20d3266d01d30d[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Nov 24 15:35:11 2020 +0000

    added motd, added sa-mpini

[33mcommit 4c2a44eb5a293bbc139cdbad5f54cf8d98abc30d[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Nov 22 03:30:41 2020 +0000

    added more crimes

[33mcommit 55ba2cd359f66f312948ab151c9342c321727b3f[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Nov 22 02:52:51 2020 +0000

    remove Automated Message:

[33mcommit 6185d48260fd8e6a0f14caca38f67aa63696c268[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Nov 22 02:41:10 2020 +0000

    added functionalities to atms, added TDMenu: callback for td menus instead of forwarding each time.

[33mcommit 4f2be158c4183207d6bb911990e414040111ac8f[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Nov 20 23:40:41 2020 +0000

    addd /editatm

[33mcommit 32c5d40fc6dab8ac03568b7041dbd99e92c32083[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Nov 20 00:48:08 2020 +0000

    move atm to server_ & recoded atm module.

[33mcommit 2f5aab76b853cf94452a18ff9102101cddf7e989[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Nov 18 16:16:37 2020 +0000

    better readme

[33mcommit 600e7be18dfb9bfce0f667bdf8184b0719faf981[m
Merge: 41267f3 226acee
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Nov 17 15:22:43 2020 +0000

    Merge pull request #46 from PatrickGTR/refactor-2021
    
    Refactor 2021

[33mcommit 226acee0814f75eab878cdf3bf6152087b4c7c07[m[33m ([m[1;31morigin/refactor-2021[m[33m, [m[1;32mrefactor-2021[m[33m)[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Nov 17 15:21:01 2020 +0000

    started player_crimes.inc

[33mcommit d66ef0f0eddb0a3571dc353432cdbd9ddb4f59b8[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Nov 16 13:53:12 2020 +0000

    added gang player load

[33mcommit 438471d48c9d68deb57911ff145731ec4d7f2273[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Nov 16 03:49:44 2020 +0000

    rewritten gang module, more optimization.

[33mcommit 4025150299b695f454cf46639626c2a91a7b06ff[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Nov 13 16:03:55 2020 +0000

    discovered mysql_tquery_file for creating tables. added auto msgs 'server_msgs.inc'

[33mcommit b609a409cf0a61085d804ed7cb0077eda2a24b18[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Nov 11 23:48:25 2020 +0000

    gang

[33mcommit be02699bf77080c1a6dcc837f01f187d598f257d[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Nov 10 02:10:42 2020 +0000

    added auto message

[33mcommit 49690c0fc0a1f5e1cb02eb038fc685109fe40707[m
Merge: 98c36d7 1828802
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Nov 10 00:07:36 2020 +0000

    Merge pull request #45 from PatrickGTR/XomoX-gang
    
    gang sys

[33mcommit 1828802388e9b0e973effb71d052c55682bd4a55[m[33m ([m[1;31morigin/XomoX-gang[m[33m, [m[1;32mxomox-gang[m[33m)[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon Nov 9 13:14:06 2020 +0800

    Fixed gang bugs and improved

[33mcommit 98c36d7e5ea4b434be5958c43ec3aebe72de00ef[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Nov 8 21:10:47 2020 +0000

    added store name, fix spacing with info_td, removed repetitive code.

[33mcommit ba16aca2bf0dfea0428aa948a275d92ba584ec4f[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Nov 8 13:19:34 2020 +0800

    Forgot to remove prints.

[33mcommit 0a07348339384e500ccee050dc14e49a4413a913[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Nov 8 13:11:01 2020 +0800

    Gang ranks update.

[33mcommit 7fc93a5c6ec8cbb94e58162295dcde32b0a41b63[m
Merge: f94101a 2d7de1f
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Nov 8 11:34:26 2020 +0800

    Merge pull request #44 from PatrickGTR/refactor-2021
    
    Refactor 2021

[33mcommit 2d7de1f97c6ff353cbf2ac09bf6d28c3ee12b2d2[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Nov 7 23:44:40 2020 +0000

    player_skin orginisation, more refactor

[33mcommit 95da2a1233774920286546c1ba7a110926de68d6[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Nov 7 20:55:52 2020 +0000

    remove discord, added pawn-env, updated samp-logger, more code refactor

[33mcommit f94101a7c0b531c7d858090192c52a705b31039a[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Oct 29 23:57:21 2020 +0000

    better debug messages

[33mcommit 5dfdc73a10cb27ecad3c74e85d2a3de2d9cd0e33[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Oct 24 20:13:03 2020 +0100

    more refactor, added better saving for weapons and hitpoints, added auto save

[33mcommit 3245e87eb25b245b75319c5bf49f5e753abd60b2[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Oct 24 18:43:47 2020 +0100

    better log output, more clean up

[33mcommit 519dbb7e82951ac45c34ddb22e878f8581c3002b[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Oct 24 18:17:42 2020 +0100

    more cleanup

[33mcommit f22890cb9987249945e54ecc23375afafbe00b0f[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Oct 24 18:04:50 2020 +0100

    added animation td to cancel anim

[33mcommit f6493ddd02a26ae5716807bc022ac1796a40a462[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Oct 24 17:40:26 2020 +0100

    refactor code, prepared statement for weapon load/save

[33mcommit 41267f36c90e1277eeae7bc57ce1e10d46134f57[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed Oct 21 23:09:33 2020 +0800

    Made health armour in players table and fixed a bug in /spec

[33mcommit 9a6664b0870aa3ac7d54c475e411339ebbf83d37[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Oct 10 21:44:48 2020 +0800

    Added Spectating system for admins

[33mcommit d48c70b5fa8fe479fb5d09effcf3e351e5e3c7fd[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon Oct 5 13:52:37 2020 +0800

    Added Saving Weapons, Armour and Fixed Burglary system

[33mcommit 5fc70637ab13906b6293a55657eca3787e540140[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Oct 2 16:38:20 2020 +0800

    Made progress2 dynamic, Added weapon saving system

[33mcommit 60a3286913ed51d8246bf28eaf21153fc86d07ff[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Aug 14 14:17:39 2020 +0800

    Update README.md

[33mcommit d4bd9465b023f5dbdb840ac9d26bbd1c7b10fe59[m
Merge: c03988f ac97679
Author: PatrickGTR <patricksubang@live.com>
Date:   Mon Aug 3 23:27:14 2020 +0100

    Merge pull request #37 from Velzius/master
    
    Bug fixes

[33mcommit ac97679aef2d10556c4becdb2265fd59e4e2dc78[m
Author: Velzius <vic.onofrio@gmail.com>
Date:   Sat Aug 1 22:45:55 2020 -0300

    Bug fixes

[33mcommit c03988fd59776d4aa6652696c431c4ec4f53ec0c[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Jul 26 04:44:40 2020 +0800

    Remove the server crash

[33mcommit 0682f192bc2e07376c5f8e73557a2a1a68fd60a2[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jul 17 17:22:37 2020 +0800

    Added Cop Mission And Discord Players online Status And Bug fixes

[33mcommit 70e5db62e68517d8c6ceb1f8a98852933536c3c4[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed Jul 15 13:21:53 2020 +0800

    Fixed SSCANF warning

[33mcommit e659893a85f583219ad3ce7225d6fd44fe42bb95[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed Jul 15 13:20:15 2020 +0800

    Fix ATM players can place while editing in a house

[33mcommit 2a1c77af49892cc3ddcb0812f656124286d7b2b1[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed Jul 15 13:07:49 2020 +0800

    atm bug fix

[33mcommit c4dafcfdde165239b10a950c765a4873871e5f9e[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Jul 14 20:45:29 2020 +0800

    Bug Fixes Added Gang System.

[33mcommit 2b66ab3418d0ea298a9225f540b097e4407c69d2[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon Jul 13 18:31:00 2020 +0800

    Fixed ATM bug Added New admin commands

[33mcommit 9f8d96eb902ffa9addd229b2774450b35d19f0e5[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Jul 12 16:56:58 2020 +0800

    Minor ACMD Fixes

[33mcommit 9151230805b1816125a15b700344e43bcb93623c[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 11 01:22:40 2020 +0800

    Updated dcc

[33mcommit b6fb64df89d58dd91fb3f0f70b5cff9b7902a343[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jul 10 14:45:18 2020 +0800

    Added players classes and army skining

[33mcommit c6e34f47c9c2a3dc3a0b5d3539fb3ae9c60e39f9[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jul 9 20:53:19 2020 +0800

    implanted more admin commands

[33mcommit b2b139386e37227e476298d9fb4555832faf90b7[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed Jul 8 20:37:55 2020 +0800

    Added bank fixed the skin bug for good

[33mcommit bc5c69d116db9514783b49029c46d93c4da392ee[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Jul 7 16:08:12 2020 +0800

    Saving Kills and Deaths and the ratio

[33mcommit 8d7a181870546f0d51910dc804c85aa63ad13022[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Jul 7 14:16:17 2020 +0800

    Fixed Dealership Fixed Player Spawn.

[33mcommit 9a9496ab1f3eb423e75cd45f4db1bcafcfa18543[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Jul 7 12:02:16 2020 +0800

    Added Score Saving Read the main.pwn temp fix player skins (again) updated td menu you can use textinfo_add on textmenu_create read td_textmenu

[33mcommit 30d3e66164546e9aa58fff9c70bfe3d704be25a7[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon Jul 6 20:17:22 2020 +0800

    Updated TDMENU you can now use TextInfo_Create

[33mcommit 73622e3bc10636e94f410da77624889207c2e805[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 15:00:55 2020 +0800

    Fix hackatm added reworked the admin notifications

[33mcommit 391e2c4b9479a5fe2ed091e2cb87f4766e95fecc[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 14:13:24 2020 +0800

    Added /hackatm

[33mcommit 9c8d1ba9fcf035b95052bd0a16c625d91e67215a[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 11:33:12 2020 +0800

    Fix setup table

[33mcommit 02f68dca76f0d6e80c951f8d90f8cd6ab7b328f1[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 10:56:53 2020 +0800

    Fixed ATM SYSTEM

[33mcommit 8df50175d3df4cf3239b123a8564830789f64153[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 10:34:04 2020 +0800

    Fix ATM take 3

[33mcommit 8d6c3209a68ce61525039084556cfa0a8405dc3b[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 10:13:26 2020 +0800

    Fix ATM take 2

[33mcommit a0466ea027f73d7268a2c2c3bd89666d0d61add7[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 08:50:08 2020 +0800

    Fix atm and dcmd_admins

[33mcommit e05454961213dc8952c43d9839288a786fe424c0[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jul 4 07:23:44 2020 +0800

    ATM update.

[33mcommit 2affa8787f5fbc1ab13679899938fe4104d1fc7e[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Jul 1 13:33:37 2020 +0100

    smoother class selection skipping

[33mcommit 3a34a52f2e16a51d4d2783e609e6a7e06333785b[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Jul 1 13:13:30 2020 +0100

    added register and last login date

[33mcommit caae37a17ac0a27af9a8d4c175c312d5436419c7[m
Merge: 2548ceb 23425b6
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 27 14:25:05 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 2548ceb475e3d2deffa4623a556bfbe6f123c0aa[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 27 14:23:29 2020 +0100

    added animations

[33mcommit fb967cd3b64523ebc5be3efbd652d60993b08149[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 27 13:44:23 2020 +0100

    added army to leo list

[33mcommit ce9f659602418315f02aa263bca89244a331e08d[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 27 13:34:01 2020 +0100

    /breakcuff fix

[33mcommit 23425b602c5ddbc0e3dd796e7b58d8cc33529697[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jun 25 02:59:46 2020 +0800

    Fixed pizza and trucker bug

[33mcommit 5c2d1c9b7c7837a7d417cf4483e668a6d8a799ae[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 23 15:10:52 2020 +0100

    bug fixes, jail bug, army vehicle bug, lotto oob

[33mcommit d203011be7a86624743853b984dc0d822de94a6f[m
Merge: 6094e1c c845b2d
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Jun 23 14:39:58 2020 +0100

    Merge pull request #34 from PatrickGTR/XomoX
    
    Merge Req to test the server

[33mcommit c845b2df5275ec62ed7d1f4142a4290a0553f04c[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Jun 23 12:29:12 2020 +0800

    Decreased the string of /a

[33mcommit 2dda66efa684e405e65c84c6bfcdad0d70121f39[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue Jun 23 12:22:41 2020 +0800

    Fixed Innocent players can enter army vehicles

[33mcommit ddc273cbffb43cbbaf7a497d5d3dbf4f7c21730c[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon Jun 22 02:34:31 2020 +0800

    Fixed Trucker Added Pizza Delivery Increased the string of /a
    
    Fixed Trucker:
    Fixed the bug,
    Improved Trucker.
    Added Pizza Delivery
    Increased the string of /a

[33mcommit 6094e1cdae5c5950c80a0caea2e07753917fe775[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 21 15:13:51 2020 +0100

    fix conflict with moneybag and briefcase, initiate lotto on script init, added moneybag

[33mcommit d0f8633a3b28faf188152754d1f3f08b4c9ba98d[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 21 13:49:27 2020 +0100

    initiate lotto variables on connect

[33mcommit 5065bc7403ec2c26e60edec7aa9a77996cff3d6b[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 21 04:55:44 2020 +0100

    minor changes to lotto

[33mcommit 4d6b51a1c1aed2e6f919dbc847e8c02fa436d5b5[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 21 04:50:42 2020 +0100

    added lotto

[33mcommit a5d00c312493e37395c11716959a48979476f731[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 21 03:11:45 2020 +0100

    24/7 a.k.a item shop, finished

[33mcommit 07ba78c7b33be0a57d00b0b7ce152e64e07fee12[m
Merge: 4352714 dd00614
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 21 02:25:52 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit dd006142b35e7fe4f1f2a7f2b83c5bb9d5bff2bc[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Jun 21 01:39:43 2020 +0800

    Fix army added /admins discord cmd fix @mention error on discord added /fly

[33mcommit 4352714979f595896ec4fb646fb92177238af4d3[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 20 17:28:52 2020 +0100

    added items, needs finishing

[33mcommit 672c0501ac956bfa07091e9782204bbfb5d73280[m
Merge: 69561bd 02fd660
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 20 16:13:22 2020 +0100

    fix time & day string issue

[33mcommit 69561bd8f5c1b8f7622ae9ae74ec294bdb9ab62c[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 20 16:11:55 2020 +0100

    fix time & day string issue

[33mcommit 02fd660b1df181d8b476de824ac5014bd387d732[m
Author: CnR XomoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 20 21:56:42 2020 +0800

    Update pawn.json

[33mcommit f704810a513ce0f777f733aa89afd52cb0bdbbcb[m
Merge: dea5b24 c876598
Author: PatrickGTR <patricksubang@live.com>
Date:   Sat Jun 20 14:53:01 2020 +0100

    Merge pull request #32 from PatrickGTR/XomoX
    
    Xomo x

[33mcommit c8765987b52f9cab61080e1e12bc3e409ed04042[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 20 21:46:23 2020 +0800

    Added Discord compatible

[33mcommit 77ee89b2434e30c3281bdb12479d97545b82b1f5[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 20 14:45:00 2020 +0100

    added gamble /gamble -> soon to be in slots machine only

[33mcommit 006d96f38596e6e912abaf8aa5a2af8957b37d7a[m
Merge: a31bc35 dea5b24
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 20 05:04:41 2020 +0800

    Merge branch 'master' into XomoX

[33mcommit dea5b24d5c1a08cab38bbc19d988bde608f6317f[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 20 03:19:08 2020 +0800

    Added when a admin uses a cmd it tells other admins

[33mcommit d6c2bf86bcaa5ce9341c7d3ca638dfcd3060f29b[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 20 02:19:48 2020 +0800

    Debugged admin commands

[33mcommit 96f504e2d2567b43a6be8c065f4b21b98087d4f8[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 19 12:52:51 2020 +0100

    add in-game and week time

[33mcommit a31bc350b1f0e9c6c63ee790e4c19367079bfc9d[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jun 19 00:08:28 2020 +0800

    Added army base system

[33mcommit 85b380886f2951b7d399cb5b2614e868d728afa4[m
Merge: 5cbdcb2 108b153
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 18 12:48:04 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 5cbdcb2672a5160139bc68463437f101e5b43de3[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 18 12:47:54 2020 +0100

    fully fix /ban (change layout) - fix /bail

[33mcommit 108b153be07e9e2316dd526c79344f4aff5637b9[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jun 18 11:20:58 2020 +0800

    Added Some Few Admin CMDS
    
    Removed /mone which a player can give them selves money and /goto which you can teleport to grotti

[33mcommit 2b34a83422bd6db9aaa9086d5a4f5a2105af07bb[m
Merge: 0d4060a cff0b3c
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 18 03:08:49 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 0d4060a722cf9e2bce8d14db516062cc89fccd8c[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 18 03:06:52 2020 +0100

    /ban fix

[33mcommit cff0b3c4ab954803b07196053074905afbaee7f8[m
Merge: d4d717a 370e27e
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jun 18 09:56:51 2020 +0800

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit d4d717a96529bfd7ef548da8362172ba412d5fe5[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jun 18 09:56:11 2020 +0800

    Fixed not disabling race checkpoint

[33mcommit 370e27e34c09f05f1ad237424a28d5d3ac2af961[m
Merge: 7c7c526 20767e9
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 18 02:51:21 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 7c7c5268fe2a39189a95b1dfd5080fbc32bd6ced[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 18 02:48:27 2020 +0100

    add catch for /ban

[33mcommit 20767e902f41e9fe16e9bbc6d561405945279158[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jun 18 09:05:24 2020 +0800

    Seperated the tester table

[33mcommit c4f7bd95ec790269f49abcb56720458ce81604b1[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu Jun 18 03:43:48 2020 +0800

    Update Tester System little debugs
    
    Added Tester:
    Tester Command will be viewed in /tcmds
    Added /settester for admin level 5
    Added cmd that you can teleport easily into interiors /interiors
    added some TCMDS: defined on utils_cmd.
    Added the Animations on burglary_system.
    Fixed Typo on /rconsetadmin

[33mcommit 6aa163e1e96514ac63528136e1776f93e1167f1c[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Jun 17 02:22:58 2020 +0100

    fix /placehit where you can placehit on yourself.

[33mcommit b1f38ceba4e59a763118082f9f289276170fe007[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 16:31:29 2020 +0100

    fix /bail

[33mcommit c09f0d8509ff994384d9645498aa4199bcfe9358[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 16:28:06 2020 +0100

    fix hostname spacing

[33mcommit 3a6aea176f9bd70dfb13427a602d366ff09e451f[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 16:25:11 2020 +0100

    add weed planting system

[33mcommit 4cf3684dcb841274793e46371edd0ffa8e8daae5[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 16:06:30 2020 +0100

    better closest player detection, add /rob cmd

[33mcommit c80b7c16508906c033d864111742fe5b243cd37f[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 15:44:01 2020 +0100

    add breakout cmd

[33mcommit dccb4dae0afdced04826cacaf0d54329eb7f87b9[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 15:32:48 2020 +0100

    add breakcuff & picklock

[33mcommit 32b12eba6775454b4907093373bf2f431b72586d[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 10:58:25 2020 +0100

    added pm, added radio for police officer, added cmds to show available cmds

[33mcommit c06ae95b5837b37008b37008523a2d60349dc451[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 16 10:01:38 2020 +0100

    define semver, define dbg_handler for server, remove debug for money change

[33mcommit 9368ca3d8302356294c1752bd54deb783c3a2f0d[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:44:26 2020 +0100

    init jail & bail on connect

[33mcommit 08d2648fbcb49c26b15d481e240553a11040d8dc[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:42:29 2020 +0100

    do not allow non civilian to change skill

[33mcommit f24abdb60874b6f3e588b4ab72be9ce4d8802bfb[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:39:58 2020 +0100

    set player colours when reconnecting, disallow non-civilian to produce crack.

[33mcommit 5db8444fbc5e3d50c386d05bf8bbcf7f506c98d5[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:27:53 2020 +0100

    fix typo playerid -> targetid

[33mcommit 7dccbb172b05f584427b8dccd4c54d7d69846c63[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:26:07 2020 +0100

    show timeleft ui

[33mcommit 1973ba8ae4b94d5f119d4d412e844e09fe772a7e[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:25:24 2020 +0100

    jailtime issue

[33mcommit 69f0830d9a263e67c5ff0cdf701a85194628a38a[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:07:34 2020 +0100

    add player_arrest.inc

[33mcommit bf157be305d637c55e979b7d4c9abbb604828637[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 05:01:38 2020 +0100

    reward player, arrest looks better now + more refactor

[33mcommit 435bf1c79f113dbe2f402761ed3672933c30fb3c[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 04:25:08 2020 +0100

    more refactor, set Player_GetClosestWanted return invalid to INVALID_PLAYER_ID instead of -1

[33mcommit c25ac89f1dcc835ab7ff1d78b6377ab08ef0b49e[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 03:53:50 2020 +0100

    remove entry from jailed table when player gets released.

[33mcommit 601954126fece1ef958a6ae8221badfcbae361bc[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 15 03:49:48 2020 +0100

    remove useless code, refactor code, use cuffs.inc api (clean up)

[33mcommit 72ef36ab9b199e51dd8c6b1702ce9163017558ca[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 14 14:13:29 2020 +0100

    remove sscanf2 from main.pwn

[33mcommit 5d7e69bb5bbbf3d811df81663260c79fe5a8e6fe[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Jun 14 14:00:49 2020 +0100

    typo fix, might cause some error in the future.

[33mcommit 56d882dedfb0b24e7f8dbc477661d00b51364c25[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun Jun 14 20:07:31 2020 +0800

    Fix sscanf

[33mcommit f3c6ccd0fa3b9b283c37f88f6228b1e29ba73480[m
Merge: 2cc84ec 018116f
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 13 22:56:13 2020 +0800

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 2cc84ecdce436805fe9bc5bfa5776b29a58e3806[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 13 22:55:46 2020 +0800

    Fixed /setadmin and .rconsetadmin

[33mcommit 018116f96876f43c37831500e9e525c93f6f39a2[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 15:52:33 2020 +0100

    changes on ban module

[33mcommit cf08fb99b27b257068c0927c8395ea6e0f6e6f75[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 15:47:31 2020 +0100

    fix ban command, parameter wrong way around

[33mcommit 3571ebb6d8259c109538ff1ce0e14e21cb8d4189[m
Merge: 23919ca 2a3cf20
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 13 22:33:07 2020 +0800

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 23919ca3b1ced75308bbf532c29a80ac7a4ed848[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 13 22:32:15 2020 +0800

    Debugged cuff and arrest

[33mcommit 2a3cf20fd1f491b873a05208632ee03db81ad2f4[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 15:27:55 2020 +0100

    health hacks ac fix proposal

[33mcommit ac84cefc5ab31e49a1c0ef2bb97c0f1507ceb354[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 15:10:30 2020 +0100

    initialise jail, and add class selection check

[33mcommit 1c4006869baf252864109e0d63397b975f8f913a[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat Jun 13 22:00:31 2020 +0800

    Fixed Burglary Bugs

[33mcommit ab9e265a23c01f5b5d13957f44d2c2eef576fb48[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 04:45:17 2020 +0100

    save player money

[33mcommit e580a1020ade9d7e37bfee2819823b326f58e7ac[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 03:23:08 2020 +0100

    stop timer & reset data when player dies while producing cocaine

[33mcommit 22cf5a405d9222d0d1deed6037738908d3ad81a0[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 03:18:08 2020 +0100

    commands -> cmds

[33mcommit a20fe6cc2a1c0bd09dee2d913d4a39545d627838[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 13 03:13:42 2020 +0100

    completely remove damage-ui, pretty useless and more like dm server.

[33mcommit d88a63cc80429ddfbc534c40ab1ad2aaf4ed75ef[m
Merge: dda4da5 54c19fc
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jun 12 14:12:55 2020 +0800

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit dda4da595c6efabea8d5cef28c77586b3f8b1f0e[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jun 12 14:12:05 2020 +0800

    Fixed little bugs

[33mcommit 54c19fc1151f3d23fc64c052a4c7c9544b64306e[m
Merge: 3941334 717b01d
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 06:51:32 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 394133409b3efcc90db5c7dd8ff5ab73d31cd436[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 06:48:06 2020 +0100

    fix issui with damage ui

[33mcommit 717b01d35a319e33890be2ccc4aefad43f24904a[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jun 12 13:47:10 2020 +0800

    Fixed Bugs
    
    Fixed trucker where you can't truck with the truck..
    Fixed Tower where you failed to get the brief case it doesn't cooldown.
    Added /get and /gotop

[33mcommit 2af9dae89f3bf2886ed4d5bfc375e1e8824c1b5a[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 06:24:06 2020 +0100

    disallow player from entering entrance while in vehicle

[33mcommit fe9447acf3759b88a0906df423f9f2d6fa2d1a1c[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 06:06:06 2020 +0100

    converted attachment to dialog_preview_model & furniture, don't depend on listid anymore. who df thought of that

[33mcommit 8a42fc1dd7e6ba6f7ad63f317000b34f0a791308[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 03:04:01 2020 +0100

    make login less boring

[33mcommit e8ce6ffe05c5b567f3007ff5ee9622749cf768df[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 01:34:06 2020 +0100

    better detection, it was replacing what sscanf was asigning before

[33mcommit 68999d4741851db0fa110ecedc43ac4d7eac1b5f[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 12 01:22:36 2020 +0100

    initialise admin variable to 0 on connect.

[33mcommit 7afe3b5a6bde0245e00937bba4e426f94c3da572[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 18:13:07 2020 +0100

    preload anims

[33mcommit 7149b59ebdd6e0e57aab86c1bd8f38ce4e135821[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 17:02:56 2020 +0100

    added crack system, fixed crash when empty param passed to cmd (related to CallLocalFunction)

[33mcommit b6c1c2439d58690abce0211ea873dfd6982d6c4a[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 14:24:30 2020 +0100

    anti-cheat

[33mcommit b0f41156972715c1fbc64a1b4e96fba2d5114984[m[33m ([m[1;31morigin/Backup[m[33m)[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 12:48:53 2020 +0100

    fix ammunation bug where you can only buy from market

[33mcommit 66f96e6f27c050729ffa81d4f3503a837b02fa6e[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 12:40:27 2020 +0100

    fix typo with setting player health to 1 instead of 100 in hospital system

[33mcommit 1ea219e1a7f7a71674465f116bc0bbcd953529f6[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 12:38:57 2020 +0100

    take bracket, colour and ID into account with join & leave UI

[33mcommit 4ea9d14cace0572a00ce5daef16d57800d739c94[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 12:32:13 2020 +0100

    fix skin spawn

[33mcommit aabccc0c5e9a39ee9b7b8ab9747ddacf12faec21[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 11:43:38 2020 +0100

    fix invalid specified id error in console when deleting a house

[33mcommit 9dc8727591d7e49ab09b125801d1b9a0b8a7593c[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 11 11:40:41 2020 +0100

    added extra protection on 'F' to enter house, initialised Player_IsInHouse on connect.

[33mcommit b81b580120c5b73f5ae4dc6c3daf79ce94fade88[m
Merge: 769912c 3992e25
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Jun 9 04:54:01 2020 +0100

    Merge pull request #30 from PatrickGTR/housing
    
    Housing + Personal Vehicle + Tons of bug fixes a.k.a dev branch

[33mcommit 3992e2526842facc720cc749cec84e5e539ee0da[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 9 04:52:47 2020 +0100

    specify dependency version, added information when player is robbing & entering personal vehicle. added vehicle owner name variable.

[33mcommit b58a126d960ae47c505398ead0218817b7e80518[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 23:28:47 2020 +0100

    decrease array size of personal vehicles, added time detection to avoid robbed recently message.

[33mcommit f67388083dd581635119f193b1de71189ef0ec59[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 14:17:38 2020 +0100

    IsPlayerInPersonalVehicle -> Vehicle_IsPersonal

[33mcommit d259173e1a3008e94462c37cbf6daf023bcc124a[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 14:15:15 2020 +0100

    fix bug with ui_wanted where hook was before the function, fix bug with componenents not being added fully.

[33mcommit fee3f36ef32600ed8abebec55a857012f9019007[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 05:40:33 2020 +0100

    smooth auto-spawn, doesn't flicker you to requestclass for a second and spawn.

[33mcommit 17fff830b37c26b2f089a92767f26cae48e2afa3[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 05:09:20 2020 +0100

    fix issue with include order when bcrypt inline has been added

[33mcommit 8ecce66d3fb9eed607a99695e78965b9ce433dc2[m
Merge: 4f6caa2 d4f051f
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 04:44:39 2020 +0100

    .

[33mcommit 4f6caa25a5b791bfce2231a7bf3c3219512b8364[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 04:43:10 2020 +0100

    indentation tab -> space

[33mcommit d4f051f421c09ad1e6151947e0037de700c34b4a[m
Merge: 2e8a7fb 769912c
Author: PatrickGTR <patricksubang@live.com>
Date:   Mon Jun 8 04:36:47 2020 +0100

    Merge pull request #29 from PatrickGTR/master
    
    bcrypt inline impl

[33mcommit 769912c7601fe6c3fc2d36569fd7e7abde6a8421[m
Merge: 5832246 2e8a7fb
Author: PatrickGTR <patricksubang@live.com>
Date:   Mon Jun 8 04:36:25 2020 +0100

    Merge branch 'housing' into master

[33mcommit 583224650725ad57dbb3f8296def1a2a1e329fa9[m
Merge: 0d9c1a9 8860ecc
Author: PatrickGTR <patricksubang@live.com>
Date:   Mon Jun 8 04:34:08 2020 +0100

    Merge pull request #28 from omcho420/master
    
    updated bcyrpt to inline

[33mcommit 8860ecc74d62b122cb36d1ab290028d62239f4a5[m
Author: omcho420 <46234261+omcho420@users.noreply.github.com>
Date:   Mon Jun 8 05:27:06 2020 +0200

    updated bcyrpt to inline

[33mcommit 2e8a7fba28592cafa62d145cd32eac597b1e5a7a[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 8 03:37:35 2020 +0100

    added grotti shop dealer & menu, ysi & prev model dialog fixed. (BUG: with components not being added completely.)

[33mcommit ef268bef862e2a7a8a5a5ad4d9109e60909d9276[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Jun 6 04:42:52 2020 +0100

    plug vsync, added savable vehicle components. NEEDS FURTHER TESTING!

[33mcommit 1963fdde469642a9349f2fef57402d26e0580bfc[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 5 17:19:32 2020 +0100

    saving & loading vehicle, destroy vehicle on disconnect, create vehicle on connect.

[33mcommit 77047c2e3cb3f8c0961afdd3465b59f67bbc0b1f[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 5 13:59:02 2020 +0100

    bug fixes, OnPlayerUpdate -> OnPlayerSecondUpdate.

[33mcommit 3e860571709b95e65af2c8bd9e57cbf6b4e17296[m
Merge: a09356a 0ecee78
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 5 13:43:02 2020 +0100

    Merge remote-tracking branch 'origin/xomox' into housing

[33mcommit a09356a81aa20b3118375af0173e114a41d30b66[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 5 13:41:16 2020 +0100

    added int & ext dealership, remove bike blocking grotti entrance, bug fixes.

[33mcommit 0ecee78289ecb40b842bf0c1b7de39f331f3469a[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri Jun 5 20:26:57 2020 +0800

    Added City Hall and Hospital
    
    Added City Hall:
    With change skill
    -todo player can select skill.
    Added Hospital:
    With heal and change skill
    Debugged saving skins once again.

[33mcommit e4bdfed697078bf5e15bd69a346f89d85d714baf[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 5 04:21:43 2020 +0100

    added vehicle dealership UI

[33mcommit f87621bc1d2043256744bb64c2af9dab2c4a62ca[m
Author: Patrick <pds2k12@live.com>
Date:   Fri Jun 5 00:54:18 2020 +0100

    login status not set when user login, temp fix for dialog preview model

[33mcommit 65e2bff002e8b41a41f7d65cc0c46a079e022ace[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Jun 4 05:55:17 2020 +0100

    added furniture system

[33mcommit 26645ee7b14b35d91b13220413b1863e669889f3[m
Merge: 1e376d1 c01cc10
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 2 16:31:05 2020 +0100

    Merge branch 'housing' of https://github.com/PatrickGTR/gta-open into housing

[33mcommit 1e376d19ee29afe895f47d1ca317ffe054677ee7[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 2 16:27:57 2020 +0100

    added saving, fixed few on the go.

[33mcommit c01cc101dc649e36b918ca53276f777a50a1d69a[m
Merge: cebc88a 0d9c1a9
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Jun 2 05:37:40 2020 +0100

    Merge pull request #27 from PatrickGTR/master
    
    update housting to latest master

[33mcommit cebc88aaaeb39a044bb3449e448ea73bb64c4102[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Jun 2 05:33:27 2020 +0100

    house system, saving required

[33mcommit 0d9c1a97d5c7a606e6ac6c362cfc7a7a0ba2d80a[m
Merge: c8d8b35 042bc38
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Jun 2 05:32:39 2020 +0100

    Merge pull request #26 from the-tiny-semicolon/master
    
    Proper README information and fix issue when compile with Zeex

[33mcommit 042bc38af16aea1239885d14be8288ab2ba18a0e[m
Merge: c125198 c8d8b35
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue Jun 2 05:32:09 2020 +0100

    Merge branch 'master' into master

[33mcommit c1251981e2d27113f3d74d6b64f880168437ce5c[m
Author: Tin Nguyen <40380704+the-tiny-semicolon@users.noreply.github.com>
Date:   Tue Jun 2 10:16:15 2020 +0700

    Remote duplicate include path to core/commands

[33mcommit 93b84cb3b4829bcba266955e2cd1fab8c01154da[m
Author: Tin Trung Nguyen <hopthucuatin@gmail.com>
Date:   Mon Jun 1 23:13:06 2020 +0700

    Proper README information and fix issue when compile with Zeex

[33mcommit c8d8b357e0c2ec9df915f2f3d97e5824e3476118[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 1 03:29:23 2020 +0100

    fix issue with newly registered players bypassing f4 check

[33mcommit e9740ba8b86505c5ff04a28f3a492fed15f1c545[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Jun 1 02:42:12 2020 +0100

    should fix F4 issue and spawn should be stable

[33mcommit 8d7001afa67e2f0182ece863b2e31201542f0c3f[m
Merge: 3fd4ac9 c7c7890
Author: PatrickGTR <patricksubang@live.com>
Date:   Sun May 31 22:46:22 2020 +0100

    Merge pull request #25 from PatrickGTR/job-sys
    
    Big improvement + refactor + bug fixes discovered when testing

[33mcommit c7c78903daf86faebe095b81d905d46ed2210f27[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 22:45:01 2020 +0100

    fix auto-spawn, excluded self from closestwanted function

[33mcommit 44791277bf9edb71ad26dd46127e3c8bef46019f[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 22:14:30 2020 +0100

    fix issue where it breaks the gamemode by having multiple queries that does the same thing

[33mcommit fde69d5ee28bb0b158308271c28840094616ff91[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 21:21:49 2020 +0100

    refactor code, fixed issue on register, fixed spawn

[33mcommit 3cbeed229b710b1613fb0ed28b07e3894e69a189[m
Merge: e9aa0f5 3e24174
Author: PatrickGTR <patricksubang@live.com>
Date:   Sun May 31 12:32:29 2020 +0100

    Merge pull request #24 from PatrickGTR/xomox
    
    Added saving Skin and money

[33mcommit 3e241743184e2fea4cf9ade9220d1b91348e24c8[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 31 16:24:27 2020 +0800

    Added saving Skin and money
    
    Added:
    player stats where saves all player's stats
    This also fixes the F4 bug where the player can freely pick a skin

[33mcommit 3fd4ac9c6df1aa9c57a559f4b6c5660986b3696e[m
Merge: e5a4513 e9aa0f5
Author: PatrickGTR <patricksubang@live.com>
Date:   Sun May 31 03:20:33 2020 +0100

    Merge pull request #23 from PatrickGTR/job-sys
    
    Job sys

[33mcommit e9aa0f5e12725c9cd046657b4f773fb24c6f7496[m
Merge: 70abde3 e5a4513
Author: PatrickGTR <patricksubang@live.com>
Date:   Sun May 31 03:19:47 2020 +0100

    Merge branch 'master' into job-sys

[33mcommit 70abde350d1caa3e18b77df1df7a3159a31ca73a[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 03:11:59 2020 +0100

    finished terrorist, finished c4, finished jail cell breach

[33mcommit a94174d095201d8aa9e5883d0d4509b7714420c7[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 02:57:52 2020 +0100

    fix bug on arrest, move jail into own module

[33mcommit e5a4513a428c672b4468af472510523273a94445[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 31 09:03:25 2020 +0800

    added the cells you might want to move

[33mcommit 2a01c424992886a4eb8179bf36984ca44d857e1e[m
Merge: 36b9d87 53cd28d
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 01:47:56 2020 +0100

    Merge branch 'master' into job-sys

[33mcommit 2055edbf35f99e503d5a2e197a7c0872be8f6ac6[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 31 08:41:29 2020 +0800

    Put if the cell is right or left

[33mcommit 53cd28dc36725ca763e087941218975d5dcad406[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 31 08:30:21 2020 +0800

    remapped lspd cells

[33mcommit 36b9d8752c894eaff6c0e6639bad2bee648670d8[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 31 00:24:17 2020 +0100

    add rapist job

[33mcommit 2ffae30c5828cef1729219406d5b19279891662d[m
Author: Patrick <pds2k12@live.com>
Date:   Sat May 30 01:27:13 2020 +0100

    it broke on last pull request

[33mcommit ce66d03f93a4b0efb4adb39e2101edeb4ce97761[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 30 08:19:24 2020 +0800

    Deleted account_jailed moved to police_system

[33mcommit 2773bfc2b407b66ea6614d97fece36eeeca65777[m
Merge: 257f44d 4ca4913
Author: PatrickGTR <patricksubang@live.com>
Date:   Sat May 30 00:57:00 2020 +0100

    Merge pull request #21 from the-tiny-semicolon/patch-4
    
    Fix indent

[33mcommit 4ca491369e2f803bbd28a4c33fcc36058328099f[m
Author: Tin Nguyen <40380704+the-tiny-semicolon@users.noreply.github.com>
Date:   Sat May 30 06:52:30 2020 +0700

    Fix indent
    
    This PR intends to:
    -   remove trailing spaces
    -   fix indentation to 4-space

[33mcommit 257f44de338c80ba540a0e3d0a12748a2f56e7eb[m
Author: Patrick <pds2k12@live.com>
Date:   Fri May 29 03:57:47 2020 +0100

    fix issue with finding playerid based on listitem

[33mcommit 9b25e40e4e65aa2d143c46922317885d0e63b06b[m
Author: Patrick <pds2k12@live.com>
Date:   Thu May 28 15:24:59 2020 +0100

    refactor account_jail.inc and cmd_bail.inc

[33mcommit 1d030dd7b9df68f3a2427c04d5e4fbae0b291a7b[m
Merge: 189773b 263d816
Author: PatrickGTR <patricksubang@live.com>
Date:   Thu May 28 15:08:31 2020 +0100

    Merge pull request #20 from PatrickGTR/jobs
    
    Player jobs

[33mcommit 263d8162f41dae01d38cb03321ef7682cd887281[m[33m ([m[1;31morigin/jobs[m[33m)[m
Author: Patrick <pds2k12@live.com>
Date:   Thu May 28 15:06:29 2020 +0100

    added textmenu handler, player colour changes now depending on wanted level

[33mcommit 1ea45991f978b058413b602b58c6bbbc31336a5f[m
Author: Patrick <pds2k12@live.com>
Date:   Thu May 28 13:50:18 2020 +0100

    added hitman & weapon dealer, fixed textdraw quality on most resolution

[33mcommit 189773ba8514c1e9ccf880aefe66be5bdb88769d[m
Merge: c59a7da bcd06d1
Author: PatrickGTR <patricksubang@live.com>
Date:   Thu May 28 00:51:13 2020 +0100

    Merge pull request #19 from PatrickGTR/xomox
    
    woop wopp!

[33mcommit bcd06d1aefa582e0af88cef3ce2b8f97a2f2609b[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu May 28 07:41:20 2020 +0800

    Changes request applied.

[33mcommit a61b3bb44b9fb51d899fd2fb351028bd0f5a88ba[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu May 28 01:56:04 2020 +0800

    Finished Arrest System
    
    Notes:Need to close the cells at LSPD

[33mcommit 553ca0cc126dedc7c238c5fdd54226a3c0f36281[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed May 27 11:26:44 2020 +0800

    Finished arrest system
    
    Notes:i can't put the JailTime[playerid] on ui_time-left in if(seconds <= 0) {
            timeLeftShown[playerid] = false;
            PlayerTextDrawHide(playerid, timeLeft[playerid]);
            stop timeLeftTimer[playerid];
        }

[33mcommit 7ee96e89f715ed5a02c48b0bcd9775dcec20798c[m
Author: Patrick <pds2k12@live.com>
Date:   Tue May 26 23:49:29 2020 +0100

    change design for ui_time_left

[33mcommit 14e5f42eb761c77da31886e3356166ea10fe7622[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 26 23:43:59 2020 +0800

    used ui_time-left in burglary system

[33mcommit 27f46d4ddf73d8222f6168c6eaffd3a4386fd1fa[m
Merge: 1e4ab4c 4fa3565
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue May 26 13:26:02 2020 +0100

    Merge pull request #18 from PatrickGTR/ui_timeLeft
    
    Time left UI

[33mcommit 4fa35655fb5e2fe4858b3b9a369bfd8228561e04[m
Merge: 104cbca 1e4ab4c
Author: PatrickGTR <patricksubang@live.com>
Date:   Tue May 26 13:25:27 2020 +0100

    Merge branch 'xomox' into ui_timeLeft

[33mcommit 104cbca5b43e32c35bb3a85d21fa506d08bafdfb[m[33m ([m[1;31morigin/ui_timeLeft[m[33m)[m
Author: Patrick <pds2k12@live.com>
Date:   Tue May 26 13:22:16 2020 +0100

    added time left ui

[33mcommit 1e4ab4ccc6de58e065edd66f70e492dc66d988c1[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 26 10:13:13 2020 +0800

    Fixed Bugs saw after testing
    
    Fixed rconsetadmin and setadmin:
    Admin_SetPlayerLevel(playerid, level);  to Admin_SetPlayerLevel(target, level);
    Fixed burglary_system:
    Changed new to static except for burglaryinfo(could be usefull in other incs)
    Fixed 2 or MMB:
    Not cuffing the player.
    Fixed the player damage.

[33mcommit c59a7da15a731e86fa79978cd327aeae3a8cb637[m
Author: Patrick <pds2k12@live.com>
Date:   Tue May 26 03:05:38 2020 +0100

    temp fix for damage & added return to damage_ui

[33mcommit f47e184497ecaf00b09581c0b19c18dba9bb6570[m
Author: Patrick <pds2k12@live.com>
Date:   Tue May 26 01:48:59 2020 +0100

    important, old way -> new way of adding dependencies

[33mcommit b874c37b99e0f4ae3ea77b36b8ab5d20394b9dd4[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 26 07:07:55 2020 +0800

    Little arrest and cuff debug
    
    Debbuged Arrest and cuff:
    When is player is not on foot instead cuffing or arresting them you will ask them to pull over

[33mcommit e76edb65fe58adf28fa553b308041312b531b9e9[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 26 04:39:10 2020 +0800

    Update Jail system
    
    Added Jail system:
    The Jail system is now loading and saving!
    Added unjail:
    A command for lvl 2 admins.
    Changes:
    Fixed ifix to Insta_Fix in the table please recreate your table.

[33mcommit 54cdc84ec88ade277df7e213a323422c8fb3e107[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 26 01:36:27 2020 +0800

    Added Cop system.
    
    Added Cop System:
    Semi finished.
    Added Cuff and Arrest:
    A CMD on cmds.
    Debbuged ui_peds:
    Where a cop can rob stores also(fixed)
    Now only civilians can rob it.

[33mcommit 0c33dfc42a9a417831f84ed33647a9d65b5e946f[m
Merge: 58b4ede 8a61070
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Mon May 25 23:00:20 2020 +0800

    Merge branch 'master' into xomox

[33mcommit 8a6107017d52f5976829237f69ec74897e6af84b[m
Author: Patrick <pds2k12@live.com>
Date:   Mon May 25 02:55:38 2020 +0100

    remove useless code and added guard clause

[33mcommit edf99e9ee818da114d45dc635e29770be9be7eaa[m
Merge: ae1483f e6b73c2
Author: PatrickGTR <patricksubang@live.com>
Date:   Mon May 25 01:26:16 2020 +0100

    Merge pull request #17 from PatrickGTR/textmenu
    
    refactorn spawn code, added medic & police spawns, added TextMenu_Hid…

[33mcommit e6b73c27db4599a02809eae1a5badb7fda4323ba[m[33m ([m[1;31morigin/textmenu[m[33m)[m
Author: Patrick <pds2k12@live.com>
Date:   Mon May 25 01:22:11 2020 +0100

    refactorn spawn code, added medic & police spawns, added TextMenu_HideSpecific

[33mcommit ae1483fd62ed538edcc3e22105918ce60b6b3981[m
Merge: 10623a6 bf55ad7
Author: PatrickGTR <patricksubang@live.com>
Date:   Sun May 24 13:42:09 2020 +0100

    Merge pull request #16 from PatrickGTR/textmenu
    
    A better TextMenu API & convert old textmenu to new

[33mcommit bf55ad7e7be7b5cdfec5fb3d5cbee35075f9c3c4[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 24 13:39:44 2020 +0100

    new textmenu api, hot fixes, removed old textmenu

[33mcommit f12ddb7d9e7af1df9bf6f4ff4099e6356d953871[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 24 02:41:09 2020 +0100

    better textmenu api

[33mcommit 10623a66331e231dd53bb3c8fae30788394e43cc[m
Merge: 1f038c6 5be5f77
Author: Patrick <pds2k12@live.com>
Date:   Sun May 24 00:08:44 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 1f038c6a161b967cee9afeed76e80fe25e96c377[m
Author: Patrick <pds2k12@live.com>
Date:   Sun May 24 00:08:38 2020 +0100

    giveplayerwantedlevel auto saves already

[33mcommit 5be5f77e345ddd929a4c54eb22d99963863371b9[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 23 11:54:24 2020 -0700

    Litte Fixes, added inv and Debugs
    
    fixed ifix:
    not loading or not giving to player
    Debugged Ammunation(again):
    Its now fully arranged Added Player_IsInAmmu(playerid) to check if player is in ammunation.
    Added latest actor_robbery.
    And last corrections.

[33mcommit e1f04c41d9da6d8660d46b5f53e9661f6c26d02b[m
Author: Patrick <pds2k12@live.com>
Date:   Sat May 23 12:57:59 2020 +0100

    remove legacy include for actor robbery, moved to sampctl version instead

[33mcommit 13f64f44813949c773393cc230b3e91a9dfde3fe[m
Author: Patrick <pds2k12@live.com>
Date:   Sat May 23 12:39:18 2020 +0100

    fix bug with race cp, remove useless code & refactor code (not fully)

[33mcommit 58b4ede4189871565c9ed95edafc336ce0b5e173[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 22 21:23:04 2020 -0700

    Final Output

[33mcommit aa64b78f1ca6f7df538086ce8147f803c4268da7[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 22 21:18:59 2020 -0700

    Fixed Request Changes

[33mcommit 495ae0cc8a093e840eb94bfa51df99a0253f2200[m
Author: Patrick <pds2k12@live.com>
Date:   Sat May 23 00:33:14 2020 +0100

    refactor trucker system

[33mcommit cdaa1072ff106e0a7e8b23426e0459bf3dbbebb8[m
Author: Patrick <pds2k12@live.com>
Date:   Fri May 22 14:56:00 2020 +0100

    hotfix, change func names & folder name

[33mcommit 5a3c5309ed2f881fbfe83f937391b7da6b5a6940[m
Merge: b6e437b 3114334
Author: PatrickGTR <patricksubang@live.com>
Date:   Fri May 22 14:24:40 2020 +0100

    Merge pull request #14 from PatrickGTR/xomox

[33mcommit 31143346fb8b1d542eca28a318c66aed68679d5f[m
Merge: aa64b78 b6e437b
Author: PatrickGTR <patricksubang@live.com>
Date:   Fri May 22 14:24:06 2020 +0100

    Merge branch 'master' into xomox

[33mcommit 54908a1f6ddcdbc5f303fb6169e844417e5d5436[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 22 06:23:08 2020 -0700

    Mechanic
    
    Added Mechanic:
    Where you can buy insta fix
    Also you can fix your car
    Fixed
    Bug that you can buy every where as long as you have the menu open.

[33mcommit 3068b7454f73c1288c606ab89918f4d782d4675a[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 22 04:13:43 2020 -0700

    Inventory update
    
    Added Inventory database
    Added Instafix Cmd
    Added cmds.inc

[33mcommit b5c4735e006adee252b3d6dd6b5a94d34b42572c[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu May 21 23:38:49 2020 -0700

    Ammunation textdraw
    
    Fixed bugs
    Added for both ammunations.

[33mcommit 1bd3b40d639cfe666ffdf0eba9f0709fe28818e4[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu May 21 18:46:41 2020 -0700

    TextDraw system
    
    Not finished yet

[33mcommit c006fa2952304f047d7b9fde4f6bc4df4177778e[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed May 20 04:10:37 2020 -0700

    tower_system debug
    
    Debugged the bug i mentioned earlier.
    Added a T map icon and rooftop entrance

[33mcommit 8dc665294e8a67b80f9aecf76ab31d8b6bf9b2e8[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 19 22:30:19 2020 -0700

    Office Tower Robbery
    
    Added Office Tower Robber:
    You need to find the briefcase
    Known Bugs:
    If you rob the Tower 2nd time it doesn't set the Hideout
    Added System Folder

[33mcommit 3ab65fcc5e298fd9119f3fa7a0d3323c7c28ecff[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 16 23:04:51 2020 -0700

    Update burglary_system and trucker_system
    
    Trucker_System:
    Fixed not sending the delivery name
    Enchanced the "new" turned into the readme.md
    Burglary_System:
    Used y_timers
    Enchanced the "new" turned into the readme.md

[33mcommit 47beb7fa5bc971dc06950171b30eb6177a849a76[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu May 14 12:59:09 2020 -0700

    Debugged burglary system
    
    Debugged the burglary system
    Added animations when robbing the safe

[33mcommit c02ae3c6e974bebdcd8984f5bc5844fd0589b783[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Wed May 13 17:17:19 2020 -0700

    Trucker System
    
    Added Some Trucker System.
    Added More Hideouts On the way.

[33mcommit 09f231dc4623519d357e8c091212fe85f09fa249[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 8 23:03:56 2020 -0700

    Added Maddog's mansion
    
    - Added Maddog's mansion
    - Added Maddog's mansion burglary
    - Renamed Maddog's mansion to
    XomoX's mansion xD

[33mcommit 7268fd9f1c0693dd8b74256106ed74fd66c258aa[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 8 15:23:18 2020 -0700

    Added a casino burglary system
    
    - Added Casino interior
    - Added Casino safe and casino shop keeper

[33mcommit feb5083f9c634cec1c0403dadc1d29aa0e2ed314[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 8 13:56:50 2020 -0700

    Added Casino interior

[33mcommit 616739a6feb42e7f20af3088d48a5536b2acc201[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 8 13:19:48 2020 -0700

    changed the hideout
    
    Changed the hideout location bugged
    Makes the race cp on the water

[33mcommit 1e562a4804ccf1eeff589116f39d7d723b5149e7[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Thu May 7 12:39:48 2020 -0700

    UPDATE
    
    Fixed The bugs
    Added RaceCheckpoints as hideouts

[33mcommit 43c686f1f3fa258d91d3745c5d6b17dd290d22db[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Tue May 5 15:29:14 2020 -0700

    UPDATE
    
    Added Bank interior
    Added a burlary
    Issues Not creating a Pickup
    Issues Not creating a Dynamiccp infront of the safe.

[33mcommit a935f615a0feb86e7ae4cb706bf6b06835f20352[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 3 18:47:56 2020 -0700

    Little Update

[33mcommit 9b5190349a3a2e3161ae0abeb3c6fcce89446381[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 3 12:58:11 2020 -0700

    UPDATE
    
    Deleted hitmansystem due to a bug will recreate it
    Added robable actors

[33mcommit 434a693da3d54ca0328d24e97e35f86f9d6439ee[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sun May 3 09:50:26 2020 -0700

    UPDATE
    
    Deleted my ui_peds
    Added robable_actor dynamic system

[33mcommit 9bfe0a559b693cfc01ed2e0fceeb872ad641b78b[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 2 12:22:07 2020 -0700

    UDATE
    
    Added ammu as robable store
    Removed colors inc found out that there's a existing one

[33mcommit 0c365bbe16dfdf7d4f8414d7c3216bdc0ab2b9e4[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 2 11:29:25 2020 -0700

    Made Hitman system
    
    Made a Hitman system
    Added  /hit [playerid] [bounty]
    Added  /hits only for hitman class

[33mcommit 19ee8344d106efc0baf737a1a03d6e8f19579b81[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 2 10:33:52 2020 -0700

    UPDATE
    
    Used the script own functions

[33mcommit 7a85238564da7f04d859d17a79eb7c7eda35262d[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 2 09:52:37 2020 -0700

    Same to this.

[33mcommit b6e437b1da6dd94205d3dee7bbbf51bdbf792f2c[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Sat May 2 09:48:48 2020 -0700

    Little debug
    
    i put some DEFAULT at the end of the job_id and wanted_level cuz its not creating the table and now it should work

[33mcommit 65cc581140add9b41873d8b79702c106c1efe89a[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 1 13:59:53 2020 -0700

    uncapitalized
    
    uncapitalized L on wanted_level

[33mcommit 49c82f1ce2ee18edddc6a4bd56d68357d5fe2559[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 1 13:55:54 2020 -0700

    UPDATE
    
    create table fixed the letters,
    Added colors.inc

[33mcommit 178167037964d184f3fe1c5873d8d6ee60680849[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 1 12:21:20 2020 -0700

    Update account_setup-players-table.inc

[33mcommit 458e06ba1edb1297980dadcacf65f93a9478920b[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 1 12:16:37 2020 -0700

    Updated

[33mcommit e468b3311c730a65d760cabd4744f3b9f248a640[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 1 12:11:41 2020 -0700

    ADDED setadmin, admin_cmd_lvl5 and rcon_cmd
    
    rcon_admin is usefull incase you're not in your account only /rconsetadmin.

[33mcommit 49b43a8a88f4a812533a8d6949155e24dd806621[m
Author: CnRXoMoX <55300557+CnRXoMoX@users.noreply.github.com>
Date:   Fri May 1 11:11:53 2020 -0700

    Added jobID and wantedLevel on create table

[33mcommit ec7163441a68de1a7f237b25f5eaa8d7e3f92bba[m
Merge: 380bfb1 fa9b201
Author: Patrick <pds2k12@live.com>
Date:   Thu Apr 30 13:51:10 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit 380bfb10f6d164a7b540ce0c17b353e7393672e7[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Apr 30 13:50:37 2020 +0100

    take 0 into account

[33mcommit fa9b201d6fb592d1d592e9d3c893c17cf84ca241[m
Author: PatrickGTR <patricksubang@live.com>
Date:   Thu Apr 30 11:22:02 2020 +0100

    Update README.md

[33mcommit 1469362183859569f75a2ec62e96baead6944b64[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Apr 30 10:39:10 2020 +0100

    added how to contribute - w.i.p

[33mcommit ac2ac17f53519fb09b5f0b659abd9f8aeeb0185b[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Apr 30 10:10:40 2020 +0100

    plug in y_utils

[33mcommit 28e2bc3401fe424e09fda04312bcf442f6c06f9b[m
Author: Patrick <pds2k12@live.com>
Date:   Thu Apr 30 09:56:30 2020 +0100

    refactor code & added attachment system

[33mcommit e372740c60b87d6e71d7ef469e72c375b6f3f3bd[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Apr 28 15:53:19 2020 +0100

    fixed SETUP_TABLE directive & move vip table creation on seprate file

[33mcommit 4ffffb95e4f9c301c1e521dce3ca0e550ccfdd6a[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Apr 28 15:27:25 2020 +0100

    - moved files to desginated area. - added server sided wanted level

[33mcommit a3298a076f76665d34d0ff37822fac9ed672fc54[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 27 02:10:01 2020 +0100

    added saving wanted level & refactor code

[33mcommit 61f33f0870ac79a81586bf8c638ad7e5f92b3217[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 27 01:44:37 2020 +0100

    added ui classes & classes + jobs

[33mcommit bd7be01a2c5c8dd70cc57db563f929662d937fed[m
Author: Patrick <pds2k12@live.com>
Date:   Sun Apr 26 01:11:58 2020 +0100

    add wanted level ui

[33mcommit 8bb4ab04a6967508e1dab3e9c0f11a5924daf510[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Apr 25 16:35:28 2020 +0100

    add skins and OnPlayerRequestClass pos

[33mcommit 712fec103b6bd31176bfb7caa60156936d48200c[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Apr 25 16:12:32 2020 +0100

    change store data name, added map icons for city hall and jeff motel

[33mcommit fbd2126f81faf8b2dff1bf130391fa64ecc170e3[m
Author: Patrick <pds2k12@live.com>
Date:   Sat Apr 25 04:24:22 2020 +0100

    added stores around ls, added cars around ls, added spawns around ls

[33mcommit a08078ead8f215edc9ca19fad395204eaab3b843[m
Author: Patrick <pds2k12@live.com>
Date:   Wed Apr 22 02:52:17 2020 +0100

    changed function names

[33mcommit 84b0b07edb3cdd2f3c12adc400cc3843998f5909[m
Author: Patrick <pds2k12@live.com>
Date:   Tue Apr 21 03:17:05 2020 +0100

    migrated the vip to prepared statements, fixed an issue with sql_datetime_format since conversion

[33mcommit 2284c7751f705bd012daa064a0f871b9367e8a24[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 17:35:43 2020 +0100

    edited readme.md

[33mcommit 4c431d056d8bbf5b562ef5a77bd151a8fe31303b[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 17:24:33 2020 +0100

    Mute_IsPLayer -> Mute_PlayerHas - better name and added account_module documentation

[33mcommit 961834d649c286bd1e9bf1e7c6e3709aee5e0ff2[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 16:53:43 2020 +0100

    set default readme for this folder

[33mcommit 088fdd3bd8e189bf2c75e8b70caf989894f9c4b8[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 16:52:14 2020 +0100

    fix format on admin_ban.inc section

[33mcommit 15bbc3aabaff116c823765ea147b3461d01ca960[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 16:50:42 2020 +0100

    finish documenting admin.md

[33mcommit b24f491aa9bc0e36f8190c866a6334aaac14ee87[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 16:29:12 2020 +0100

    add admin.nd documentation

[33mcommit 6286f177e9658892d0895be0249c352edd18af6c[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 16:12:03 2020 +0100

    admin_account module to prepared statements.

[33mcommit 3ec811ac48887e7433bc79c49af3f60827a55f3e[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 15:29:08 2020 +0100

    initial commit

[33mcommit ba492d68e607de3c41a7bdba12381c95aa072ffe[m
Merge: fe65c81 a5ebbcd
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 15:28:13 2020 +0100

    Merge branch 'master' of https://github.com/PatrickGTR/gta-open

[33mcommit fe65c81c2f8521815a984d583219c8977ce68731[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 15:19:55 2020 +0100

    initial commit

[33mcommit a5ebbcd21eed949d6fb55963b01271dd47f8313b[m
Author: PatrickGTR <patricksubang@live.com>
Date:   Mon Apr 20 15:16:06 2020 +0100

    Initial commit

[33mcommit 56652355866a450c43d78f73ee1313b335afe74c[m
Author: Patrick <pds2k12@live.com>
Date:   Mon Apr 20 15:13:19 2020 +0100

    initial commit
