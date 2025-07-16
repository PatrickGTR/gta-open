This program attempts to find old untagged and const-incorrect code and upgrade it.  There are many pre-defined upgrade replacements and you can create your own either manually or automatically.

 Usage
-------

To replace most native declarations and hooks with const-correct equivalents use:

```
./upgrade --scans const ../qawno/include
```

This will load all the replacements from `./const.json` and apply them to every file recursively in `../qawno/include`.

If you don't want to apply the changes immediately use:

```
./upgrade --report --scans const ../qawno/include
```

Which will instead just tell you of the changes to be made.

 Tag Example
-------------

Given the following file:

```pawn
native SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);
SetTimer("MyFunction", 2000, 0);
```

And parameters:

```
--scans tags ../qawno/include
```

The report output will be:

```
Scanning file: D:\open.mp\upgrade\example.inc

    @@ -1,1 +1,1 @@ Add tags to `SetPlayerObjectMaterialText`
    -native SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128,
    +native bool:SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, OBJECT_MATERIAL_SIZE:materialsize = OBJECT_MATERIAL_SIZE_256x128,
    @@ -1,1 +1,1 @@ Add tags to `SetPlayerObjectMaterialText`
    -native bool:SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, OBJECT_MATERIAL_SIZE:materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0)
    +native bool:SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, OBJECT_MATERIAL_SIZE:materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT)
    @@ -2,1 +2,1 @@ Add enums to `SetTimer`
    -SetTimer("MyFunction", 2000, 0)
    +SetTimer("MyFunction", 2000, false)
```

The replace output will be:

```pawn
native bool:SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, OBJECT_MATERIAL_SIZE:materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
SetTimer("MyFunction", 2000, false);
```

 Const Example
---------------

Given the following file:

```pawn
native SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);
SetTimer("MyFunction", 2000, 0);
```

And parameters:

```
--scans const ../qawno/include
```

The report output will be:

```
Scanning file: D:\open.mp\upgrade\example.inc

    @@ -1,1 +1,1 @@ Add `const` to `SetPlayerObjectMaterialText`
    -native SetPlayerObjectMaterialText(playerid, objectid, text[],
    +native SetPlayerObjectMaterialText(playerid, objectid, const text[],
    @@ -1,1 +1,1 @@ Add `const` to `SetPlayerObjectMaterialText`
    -native SetPlayerObjectMaterialText(playerid, objectid, const text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial"
    +native SetPlayerObjectMaterialText(playerid, objectid, const text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial"
```

The replace output will be:

```pawn
native SetPlayerObjectMaterialText(playerid, objectid, const text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);
SetTimer("MyFunction", 2000, 0);
```

 Double Example
----------------

You can apply multiple replacements one after the other.  Combining the replacements above:

```
./upgrade --scans const ../qawno/include
./upgrade --scans tags ../qawno/include
```

Gives:

```pawn
native bool:SetPlayerObjectMaterialText(playerid, objectid, const text[], materialindex = 0, OBJECT_MATERIAL_SIZE:materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
SetTimer("MyFunction", 2000, false);
```

 Generation
------------

To create your own replacements file for a newly tagged function you need the definitions of the values, and the new prototype of the function using `$` in place of the tag in `_generate.json`:

```
{
	"enum": "enum Colour: { RED, GREEN, BLUE }",
	"code": "stock SetIndexedColour(playerid, $:colour)"
}
```

Then use the generate command:

```
./upgrade --generate
```

This will print the upgrade `.json` for replacing all similar declarations (a *similar* declaration being one that looks like `Prefix_Name` where `Prefix_` is optional and `Name` is the function name specified) and all uses.  The uses will attempt to find existing calls that look like `SetIndexedColour(playerid, 2)` and replace them with their tagged constant equivalents: `SetIndexedColour(playerid, BLUE)`.

 Regex
-------

This code uses regular expressions to perform the replacements.  Don't ask why.  Anyway, in order to support things like nested brackets it uses PCRE regex with *subroutines* in the searches, and `PCRE2_SUBSTITUTE_EXTENDED` in the replacements ([actually just one feature](https://stackoverflow.com/questions/34198247/multiple-replacement-with-just-one-regex), and that was re-implemented for this release).  The file `_define.json` is automatically included with every run and contains many pre-made definitions of various pawn constructs.  For example:

```json
		"binary": "0[bB][01]++(?:_[01]++)*+",
```

That is the full definition to match any binary number in pawn (`0b01001`, `0B0_1`, etc).  It uses `++` and `*+` for possessive matching to vastly reduce backtracking in the processing.  PCRE has a very high default backtracking limit of 10,000,00; but before making many of these subroutines possessive this was being exceeded regulary by failing matches.  The majority of these defines will not match leading and trailing spaces, so these must be dealt with in every search, the exception is `expression` because it deals with arbitrary internal whitespace in a lazy manner that makes it very greedy.  They are also all non-capturing, which is why some uses may copy these defines in to a match directly in order to capture a part of it (most commonly done with parameter names).

 Notes
-------

* Most defines aren't needed.

There are very strict specific defines for various number types (float/hex/boolean), symbols, and more.  The truth is that for most use-cases this specificity is not needed and isn't used.  When scanning for an expression the system only needs to know that two brackets are matched for example, it doesn't need to know that the stuff within the brackets is a fully conforming hex number for example.  Even the strict symbol definition is barely used, so this will match names that start with numbers, even though it shouldn't.

* Replacements are ordered.

So for example `Upgrading hooks to decorators` comes before `Adding 'CLICK_SOURCE' tag to 'OnPlayerClickPlayer'`, and the latter only looks for `public|forward|@hook` not `public|forward|hook|HOOK__|@hook`, because it will know that the other two can't exist any more.  Hence why they use an array.

Defines are not ordered, hence why they use an object.

* Why does this use PCRE.NET instead of the inbuilt regex grammar?

Simple - while the inbuilt grammar does have *expression balancing* which can be used to match `()`s in expressions it doesn't have *subroutines*, so while the complex expressions **can** be built up, they can't be abstracted.  Using PCRE allows things like the regex for a function parameter to be placed in a separate `DEFINE` and reused in all the scanners by name.  The .NET version would require those expressions to be copied and pasted in to every scanner; which would entirely obfuscate their basic use and require massive updates for every single bug fix.

* Use `--debug` to view the regex being run.

Especially useful for trying to figure out why a replacement you think should have been made wasn't.

 Writing Replacements
----------------------

### Basic Procedures

The core of the replacement system is regex ([yes, I know](https://xkcd.com/1171/)), this may seem inadequate for most situations, but it uses a lot of pre-defined procedures to enable things like matching a parameter, a declaration, or even an entire nested expression.  Fortunately pawn is fully deterministic in its parsing, so the scanners disable backtracking so that match failures don't explode.  Most of these procedures are also tightly matching, so `&symbol` will match any properly named symbol (starts with a letter, `_`, or `@`; and followed by any of those or a number), but will not consume any trailing whitespace.  Thus the majority of the scanners will use `\s*+` a lot (non-backtracking whitespace).  The pre-defined procedures are:

* `&symbol` - Any properly named pawn symbol (defines, functions, variables, keywords, etc).
* `&prefix` - The first half of a method-like function, such as `Command_` in `Command_GetName`.
* `&float` - A floating-point number, including `-`, the `_` separator, and exponents.
* `&hex` - A hexadecimal number, including the `_` separator.
* `&binary` - A binary number, including the `_` separator.
* `&integer` - An integer, including `-` and the `_` separator.
* `&character` - A character literal, with special handling of `'\''` and `'\\'`.
* `&string` - A string literal, with special handling of `"\""` and `"\\"`.
* `&operator` - Any of the pawn operators such as `*` or `>>>=`.
* `&number` - Any type of number - float, binary, hex, or decimal.
* `&tag` - One or more tags, so will match `File:` or `{Float, _}:`.
* `&varargs` - `...` at the end of a function declaration, optionally with a tag.
* `&expressionpart` - Used internally by the other expression procedures.
* `&expression` - A complete expression, ended by either `,`, `;`, or an unmatched closing bracket of some type.  Fully handles nested expressions so `(a, b)` can be matched as a *single* expression when being given as, say, a parameter to a function.  This is often the most useful procedure to use when matching code calling your functions to be replaced.  Although it theoretically encompasses many of the above procedures such as numbers and symbols it uses shortcuts by just matching any string of numbers, letters, and operators; without actually caring if the resulting code is technically valid.  Note that while most other procedures do not consume trailing space this one does because it uses some lazy techniques to more quickly match things that look vaguely like expressions.
* `&squarebrackets` - An expression between `[]`s.  Expressions are ended by unmatched brackets, so this consumes the first one, then uses `&expression`, then checks for the closing one.  May contain multiple expressions separated by `,` or `;` within the brackets.
* `&roundbrackets` - An expression between `()`s.  Expressions are ended by unmatched brackets, so this consumes the first one, then uses `&expression`, then checks for the closing one.  May contain multiple expressions separated by `,` or `;` within the brackets.
* `&curlybrackets` - An expression between `{}`s.  Expressions are ended by unmatched brackets, so this consumes the first one, then uses `&expression`, then checks for the closing one.  May contain multiple expressions separated by `,` or `;` within the brackets.
* `&anglebrackets` - An expression between `<>`s.  Expressions are ended by unmatched brackets, so this consumes the first one, then uses `&expression`, then checks for the closing one.  May contain multiple expressions separated by `,` or `;` within the brackets.  This one is for special arrays, but has not been fully tested in some situations for cases like `new special:array<5 < 6>;`, just don't do that!
* `&parameter` - Any parameter declaration in a function declaration.  This is more restrictive than a full expression as it must resemble `[const] [&][Tag:]name[size][= default]`; however, both array sizes and default values may be full expressions.
* `&const` - Like `&parameter`, but must include `const`.
* `&nonconst` - Like `&parameter`, but must not include `const`.
* `&untagged` - Like `&parameter`, but must not include a tag, `const`, or an array size.
* `&parameterlist` - All the parameters in a function declaration.  Includes the `()`s surrounding them, then naught or more parameters, optionally ending with `...`.
* `&declaration` - A symbol with a tag.
* `&publics` - A collection of keywords known to be used to declare public functions.
* `&stocks` - A collection of keywords known to be used to declare normal functions.
* `&start` - The start of a line, including any leading space.

All of these procedures are completely non-capturing so that group references in the replacement are completely obvious and predictable.

### Basic Example

Let's look at a simple example that converts:

```pawn
native SendChat(text[]);
```

To:

```pawn
native SendChat(const text[]);
```

To match the start of the function we look for the start of a line, followed by `native`, at least one space, then the function name:

```
((?&start))native\s+SendChat
```

`((?&start))` is a reference to a named procedure `(?&start)`, inside a capture group from the outer `()`s.

We then look for a parameter list containing one parameter, which shouldn't include `const`.  Again, inserting `\s*` anywhere that spaces *may* appear, or `\s+` anywhere that spaces *must* appear.  `\(` matches a literal bracket, it doesn't start a capture group; same for `\)`:

```
\s*\(\s*((?&nonconst))\s*\)\s*;
```

Again, we use double brackets around the parameter without `const` to capture (and later re-use) the name.  There are two capture groups - the indentation at the start of the line and the name (or rather the full declaration) of the parameter.  These are used in the replacement as `$1` and `$2`:

```
$1native SendChat(const $2);
```

Adding a description to this replacement gives us the full code, with one important change.  Because the replacements are defined in JSON we need to escape all the `\`s in the regex so it can be loaded correctly, leading to:

```json
		{
			"description": "Add `const` to `SendChat`",
			"from": "((?&start))native\\s+SendChat\\s*\\(\\s*((?&nonconst))\\s*\\)\\s*;",
			"to": "$1native SendChat(const $2);"
		}
```


This will match any of the following variants:

```pawn
    native SendChat ( chat[] );
native SendChat (text [ ]);
native    SendChat(the_message[]);
```

And replace them with:

```pawn
    native SendChat(const chat[]);
native SendChat(const text [ ]);
native SendChat(const the_message[]);
```

You could use more capture groups to exactly replicate all of the spacing, but there's no real need to.  Note, however, that spaces within a group, such as in `text [ ]` is preserved as the capture group copies the entire thing; but trailing spaces aren't captured.

### Real Example

The file *const.json* already contains a definition for upgrading `SendChat`, and it is far more complex than the one we just derived.  Why?

First, it handles hooks as well.  If we want to const-correct `SendChat` we must also want to const-correct any ALS and y_hooks hooks of `SendChat` as well.  This system for the most part assumes a fairly consistent naming scheme for hooks, i.e. `Module_HookedFunction`, so if an anti-cheat include were to hook `SendChat` it might name the internal version `AC_SendChat`.  This is precisely why the procedure `&prefix` was declared in the first place, and is added to the search expression in a capturing group.

Secondly hooks are generally `stock` or `@hook`, not `native`, so we need to preserve the declaration type as well, via `((?&stocks))`.

Finally, some hooks might already contain `const`.  Surely in that case they can be skipped?  In the case of `SendChat` theoretically yes they could, there's no point adding `const` when `const` is already there, but `ApplyActorAnimation` shows why we still search for them.  This function has two parameters that both need to be made `const` - `animationLibrary` and `animationName`.  This gives four possibilities - 1) neither parameter is `const`, 2) ony the first parameter is `const`, 3) only the second parameter is `const`, or 4) both parameters are `const`.  Again in the last case we don't need to do anything, but for the other three cases we do; either with three separate replacements one for each case, or with a single replacement that makes the `const` optional and ignored.  Doing it this way does mean that the const-correct version is also matched without a lot of extra work, but it isn't worth fixing because the result is a no-op.  `SendChat` only has one parameter so doesn't need this special consideration, but all the const-correction replacements were auto-generated so it does anyway.  Hence `(?:const\s+)?((?&nonconst))` which optionally finds `const`, ignores it (non-capturing group), then captures a parameter without `const`; instead of just using `((?&parameter))`.

The final result is thus (with `\\` escapes):

```json
		{
			"description": "Add `const` to `SendChat`",
			"from": "((?&start))((?&stocks))\\s+((?&prefix))SendChat\\s*\\(\\s*(?:const\\s+)?((?&nonconst))\\s*\\)",
			"to": "$1$2 $3SendChat(const $4)"
		}
```

This will match any of the following variants:

```pawn
native SendChat(const chat[]);
stock AC_SendChat(message[])
{
}
@hook(.function = "SendChat") My_SendChat(the_message[])
{
}
```

And replace them with:

```pawn
native SendChat(const chat[]);
stock AC_SendChat(const message[])
{
}
@hook(.function = "SendChat") My_SendChat(const the_message[])
{
}
```

Strictly under the semantics of y_hooks this is also a hook of `SendChat`, but isn't detected without using the `Module_Func` naming scheme:

```pawn
@hook(.function = "SendChat") OtherName(the_message[])
{
}
```

### Another Example

Someone wanted to replace all instances of `va_SendClientMessage` with `SendClientMessage` when there were only three parameters, i.e. when there was no formatting being done and thus the formatting version was pointless to be called.  This could be done by the compiler with some defines, but only if the function is always on a single line.  That's maybe not a terrible assumption to make, but this tool has no such limitation.  As it happens, I did add this short-circuiting feature to y_va natively anyway, but the replacement method is documented here for completeness anyway.  This is looking at function calls, not function declarations, so all the parameters become full expressions in the search, and we only care about a single function's name with exactly three parameters:

Match the function name with `(`:

```
va_SendClientMessage\s*\(
```

Match the first parameter with `,`.  Note that we do not need extra `\s*`s here because expressions contain all spaces always, they are the main procedure that does so:

```
((?&expression)),
```

Repeat for the second parameter:

```
((?&expression)),
```

And the final one, which must be ended by `)` because we want exactly three.  If we wanted an arbitrary the search would be something like `((?&expression),)+((?&expression)\))`:

```
((?&expression))\)
```

`{2}` is also an option here for the first two parameters, but the code is clearer as-is:

```json
		{
			"description": "Replace `va_SendClientMessage` with `SendClientMessage` when there is no formatting involved",
			"from": "va_SendClientMessage\\s*\\(((?&expression)),((?&expression)),((?&expression))\\)",
			"to": "SendClientMessage($1,$2,$3)"
		}
```

