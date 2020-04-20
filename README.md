# gta-dm

[![sampctl](https://img.shields.io/badge/sampctl-gta--dm-2f2f2f.svg?style=for-the-badge)](https://github.com/Patrick/gta-dm)

Run this gamemode in two line!
```bash
sampctl package install
sampctl package run
```

# MySQL Table Structure 

Table Name | Relationship
--- | --- |
[players] | Parent
[admins] | child of players
[vips] | child of players
[bans] | Parent (standalone)

# Credits
**Thanks to**

Name | Message
--- | --- |
[Southclaws] | Includes, snippets from Scavenge Survive, sampctl.
[maddinat0r] | MySQL
[Y_Less]     | for YSI Library, used a lot throughout the code.
[Zeex]       | amx_assembly, crashdetect, indirection
[Slice]      | formatex

Very special thanks to
**SA:MP Team past, present and future - SA:MP.**

