The Cfluviurrh Programming Language
================================

_Cfluviurrh_ is believed to be the first programming language for writing
programs that can *feel*.  Cfluviurrh defines a mechanism by which a program
can be instructed to experience particular emotions.

You might, thus, on first blush, consider Cfluviurrh to be unimplementable,
as computers are not capable of experiencing emotions (you guess.)

However, this is demonstrably untrue.  It is simply that, to be correctly
implemented, Cfluviurrh must be implemented for a system that we know is
capable of experiencing emotions.

For example, it could be implemented as a contractual obligation for a
[method actor][], or similar professional capable of feeling emotions on
demand; this individual would be required to read a program text written in
Cfluviurrh, and carry out its instructions, feeling the specified emotions
at the required points in the program.

Or, in the approach the reference implementation takes, an electronic
computer may co-operate with a contractually obligated individual termed
the "emoter".  The computer executes all the parts of the program which do
not necessitate emotional experience, and prompts the emoter to experience
emotions on behalf of the running program when required.

[method actor]: http://en.wikipedia.org/wiki/Method_acting

Design
------

### Program State ###

The state of a running Cfluviurrh program consists of an unlimited number of
registers, each of which can contain a non-negative integer of unlimited
size.  (Of course, a particular implementation may impose its own limits
here, as we can't expect computers to be infinite [I guess.])

The registers are indexed by number, starting at zero; the first twenty-six
(registers 0 to 25) also have names, `a` through `z`.  Initially, every
register contains a zero value.

There is also a special value called the _instruction pointer_ (IP), which
indicates which character in the Cfluviurrh program will be executed next.
As statements are executed, the IP is advanced to the next statement in the
program text (except in the case of a jump, described below.)  The IP
initially refers to the first character of the program.

There is also a special value called the _emotion bank number_, which is
initially zero.  An implementation must implement emotion bank zero,
but need not implement any other emotion banks, nor need it implement
emotion bank switching.  All emotion banks other than zero are undefined
and reserved for future use.

### Syntax ###

A statement is either:

*   _whitespace_ (a space, tab, newline, or carriage feed character);
    nothing happens when this is executed, the IP is simply advanced
    to the next character.
*   a _comment_, which begins with `(`; the IP is advanced to one
    character past the next `)` character in the program, with nothing
    else happening.  Comments do not nest.
*   a _label_, which is a `:` followed by any printable character
    (called the _label name_).  The IP is advanced to one character past
    the label name; nothing else happens.
*   a _register reference_, followed by an operator.  A register reference
    is a lowercase letter from `a` to `z`, which refers to the register
    with the same name, *or* an uppercase letter from `A` to `Z`, which
    refers to the register with the index given by the contents of the
    register with the corresponding lower-case name.  (So if register `a`
    contained the number 4, `A` would refer to register `e`.)

There are several subcases for the syntax of a statement which begins
with a register reference.  These are:

*   an _assignment_, which is where the register reference is followed
    by a `=` character, which is followed by a value.  A value can
    be either a register reference, in which case the value is taken
    from the register being referred to, or it may be a literal
    digit from `0` to `9`, in which case it is the value of that
    digit as an Arabic numeral.  Thus, `a=1`, `b=B`, and `R=4` are
    all valid assignment statements, but `7=a` is not.
*   a _modifying assignment_, which is where the register reference is
    followed by one of the characters `+`, `-`, `*`, or `/`, which is
    followed by a `=` character which is followed by a value.  The
    register being referred to has the value added to it, subtracted
    from it, is multiplied by the value, or is divided (integer
    division, rounding down) by the value, respectively, based on the
    operator character.  Thus, `a+=1`, `a*=2`, and `F/=f` are all
    valid modifying assignments.
*   a _label location assignment_, which is where the register reference
    is followed by a `@` character which is followed by a `=` character
    which is followed by a label name.  A label with this label name
    is sought in the program and, if found, the position of the label
    in the program text (with 0 being the position of the first character
    of the program, and with all characters, including whitespace, having
    sequential positions within the program) is written to the register.
    If there are multiple labels with the same label name, the one closest
    to the start of the program text is chosen.  If a matching label is
    not found, "an error occurs", whatever that means exactly.
*   an _output statement_, which is where the register reference
    is followed by a `>` character.  The ASCII character with the same
    value as the contents of the register will be written to the program's
    output stream.  If the value of the register is outside of the range
    0 to 127, "an error occurs".
*   an _input statement_, which is where the register reference
    is followed by a `<` character.  An ASCII character is retrieved from
    the program's input stream, and its value is written into the register.
*   a _jump statement_, which is where the register reference is followed
    by a `?` character, followed by a _conditional_.  A conditional is a
    value, followed by one of the characters `=`, `>`, or `<`, followed by
    a value.  A conditional, when evaluated during a program run, is either
    true or false.  A conditional has the meaning you would probably
    expect; `2=2` is true, `4>5` is false, and `A<2` is true if the `a`
    register contains 4 and the `e` register contains 1.  If the
    conditional is true, the IP is set to the value found in the register
    referred to by the register reference; otherwise, the IP advances
    as usual.  Either way, an emotion is experienced (see below) every
    time a jump statement is executed.
*   an _emotion bank switch statement_, which is where the register
    reference is followed by a `=` followed by a `>`.  The emotion bank
    is switched to the value in the register.  If that emotion bank is
    not supported by the implementation, "an error occurs".

Note that whitespace and comments are not allowed inside any statement
which begins with a register reference.

The input stream and output stream are implementation-defined concepts.

If division by zero is attempted, "an error occurs".

### Experiencing Emotions ###

Whenever a jump statement is executed, an emotion is experienced, at
a certain intensity level.

The emotion being experienced, and the intensity level, depends on the
currently active emotion bank.  Only emotion bank zero is described here.

The contents of the first twenty-six registers, at the point in time that
the emotion is to be experienced, are summed, modulo 74, to obtain an
emotion number.  The emotion number refers to the following table; it
is consulted to obtain the emotion to be experienced.

*   0: sadness
*   1: sorrow
*   2: despair
*   3: worry
*   4: depression
*   5: misery
*   6: melancholy
*   7: wistfulness
*   8: disappointment
*   9: regret
*   10: longing
*   11: impatience
*   12: anger
*   13: hostility
*   14: rage
*   15: hatred
*   16: disgust
*   17: contempt
*   18: envy
*   19: arrogance
*   20: betrayal
*   21: hurt
*   22: grief
*   23: remorse
*   24: shame
*   25: embarrassment
*   26: guilt
*   27: timidity
*   28: loneliness
*   29: annoyance
*   30: frustration
*   31: confusion
*   32: shock
*   33: angst
*   34: anguish
*   35: anxiety
*   36: apathy
*   37: vindication
*   38: gratitude
*   39: hope
*   40: awe
*   41: wonder
*   42: surprise
*   43: pity
*   44: boredom
*   45: apprehension
*   46: distrust
*   47: dread
*   48: horror
*   49: loathing
*   50: terror
*   51: panic
*   52: hysteria
*   53: pride
*   54: anticipation
*   55: curiosity
*   56: boldness
*   57: excitement
*   58: thrill
*   59: zeal
*   60: enthusiasm
*   61: calmness
*   62: contentment
*   63: satisfaction
*   64: happiness
*   65: bliss
*   66: joy
*   67: ecstasy
*   68: euphoria
*   69: admiration
*   70: desire
*   71: passion
*   72: love
*   73: lust

(While some of the above may not be emotions per se, and while some
combinations, such as "faint zeal", "mild rage", and "extreme apathy" may be
tricky to express, this does not detract from the bare fact that Cfluviurrh
*does* support experiencing emotions.)

There are five intensity levels, listed in the following table.  To find the
intensity level of an emotion to be experienced, each of the first twenty-six
registers are multiplied by three, modulo five, and this set of values is
summed, modulo five.

*   0: faint
*   1: mild
*   2: moderate
*   3: marked
*   4: extreme

Discussion
----------

Because every label name can only be a single printable character, it might
appear that the number of jump destinations in a program is limited to 95.

This is not true, as labels are only a convenience.  You can load any value
you like into a register, then jump to that position in the program text.

In fact, there is nothing stopping you from jumping inside a comment, with
a label or otherwise.  In fact, from this perspective, comments could be
somewhat valuable control flow structures; consider

    ... (:A ... (:B ... () ...

Execution coming in from the left will skip this "block"; execution coming
in at the `:A` label will skip the "inner block", and execution coming in
at `:B` will only execute the "inner block".

Happy Cfluviurrhing!  (Or sad Cfluviurrhing, or timid Cfluviurrhing, or...)  
Chris Pressey  
Winnipeg, Manitoba  
August 26, 2012
