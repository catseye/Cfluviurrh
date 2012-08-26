/*
 * cfluviurrh.c
 * reference interpreter for
 * the Cfluviurrh programming language, version 1.0
 * Copyright (c)2012, Chris Pressey, Cat's Eye Technologies
 * covered under a BSD-style license: see LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Note that these are arbitrarily limited in this implementation --
 * the language itself does not impose limited on the number of
 * size of registers, or size of the program.
 */
#define MEMTYPE int
#define MEMSIZE 8000
#define PROGSIZE 8000

MEMTYPE mem[MEMSIZE];
char program[PROGSIZE];

/*
 * Prototypes
 */
void die(const char *, char);
MEMTYPE get_ref(char);
MEMTYPE get_val(char);
void advance_ip(const char **);
int is_whitespace(char);
int is_op(char);
MEMTYPE do_op(char, MEMTYPE, MEMTYPE);
MEMTYPE find_label(const char *, char);
void load_program(const char *);
void emote(MEMTYPE, MEMTYPE);
void contractually_obligate_emoter(void);

/*
 * Subroutines
 */
void
die(const char *msg, char c)
{
    fputs(msg, stderr);
    if (c != '\0') {
        fputs(": '", stderr);
        fputc(c, stderr);
        fputs("'", stderr);
    }
    fputs("\n", stderr);
    exit(1);
}

MEMTYPE
get_ref(char c)
{
    if (c >= 'a' && c <= 'z') {
        return (MEMTYPE)(c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
        return mem[(MEMTYPE)(c - 'A')];
    } else {
        return -1;
    }
}

MEMTYPE
get_val(char c)
{
    int ref;

    if (c >= '0' && c <= '9') {
        return (MEMTYPE)(c - '0');
    }
    ref = get_ref(c);
    if (ref < 0 || ref >= MEMSIZE) {
        die("invalid register reference", c);
    }
    return mem[ref];
}

void
advance_ip(const char **c)
{
    (*c)++;
    if (**c == '\0') {
        die("premature end of program", (char)0);
    }
}

int
is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int
is_op(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '@';
}

MEMTYPE
do_op(char op, MEMTYPE lhs, MEMTYPE rhs)
{
    if (op == ' ') {
        return rhs;
    } else if (op == '+') {
        return lhs + rhs;
    } else if (op == '-') {
        return lhs - rhs;
    } else if (op == '*') {
        return lhs * rhs;
    } else if (op == '/') {
        return lhs / rhs;
    } else {
        return lhs;
    }
}

MEMTYPE
find_label(const char *s, char label)
{
    int i;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ':' && s[i+1] == label) {
            return i;
        }
    }
    return -1;
}

void
load_program(const char *filename) {
    FILE *in;
    int i, c;

    if ((in = fopen(filename, "r")) == NULL) {
	perror("Can't open program file for reading");
	exit(1);
    }
    for (i = 0; i < (PROGSIZE-1) ; i++) {
        c = fgetc(in);
        if (c == EOF) {
            break;
        }
        program[i] = (char)c;
    }
    program[++i] = '\0';
    fclose(in);
}

/*
 * Emoting Subsystem
 */
#define EMOTIONSIZE 74
const char *emotion[] = {
    "sadness",
    "sorrow",
    "despair",
    "worry",
    "depression",
    "misery",
    "melancholy",
    "wistfulness",
    "disappointment",
    "regret",
    "longing",
    "impatience",
    "anger",
    "hostility",
    "rage",
    "hatred",
    "disgust",
    "contempt",
    "envy",
    "arrogance",
    "betrayal",
    "hurt",
    "grief",
    "remorse",
    "shame",
    "embarrassment",
    "guilt",
    "timidity",
    "loneliness",
    "annoyance",
    "frustration",
    "confusion",
    "shock",
    "angst",
    "anguish",
    "anxiety",
    "apathy",
    "vindication",
    "gratitude",
    "hope",
    "awe",
    "wonder",
    "surprise",
    "pity",
    "boredom",
    "apprehension",
    "distrust",
    "dread",
    "horror",
    "loathing",
    "terror",
    "panic",
    "hysteria",
    "pride",
    "anticipation",
    "curiosity",
    "boldness",
    "excitement",
    "thrill",
    "zeal",
    "enthusiasm",
    "calmness",
    "contentment",
    "satisfaction",
    "happiness",
    "bliss",
    "joy",
    "ecstasy",
    "euphoria",
    "admiration",
    "desire",
    "passion",
    "love",
    "lust"
};

#define INTENSITYSIZE 5
const char *intensity[] = {
    "faint", "mild", "moderate", "marked", "extreme"
};

void
emote(MEMTYPE e, MEMTYPE i)
{
    printf("[EMOTER: please genuinely experience %s %s and press Enter] ",
           intensity[i], emotion[e]);
    do {
        i = getchar();
    } while (i != '\n');
}

void
contractually_obligate_emoter(void)
{
    int c;

    printf(
      "[By running this program, you agree to act as the EMOTER.    ]\n"
      "[The EMOTER may be asked to perform certain limited tasks    ]\n"
      "[on behalf of this program, tasks that the system on which   ]\n"
      "[this program is running may not be capable of.              ]\n"
      "[In particular, you may be asked to express certain emotions.]\n"
      "[Your experience of these emotions be genuine.               ]\n"
      "\n"
      "[Do you agree to act as the EMOTER?                          ]\n"
      "[If so, press the letter 'Y' on your keyboard, then Enter.   ] ");
    c = getchar();
    if (c != 'y' && c != 'Y') {
        printf("[Goodbye.]\n");
        exit(0);
    }
    while (c != '\n') {
        c = getchar();
    }
}

/*
 * Main
 */
int
main(int argc, char **argv)
{
    const char *ip;
    MEMTYPE ref, val, val2, result;
    char op;
    FILE *input, *output;

    if (argc < 4) {
        die("usage: cfluviurrh program-file input-file output-file", (char)0);
    }

    load_program(argv[1]);
    memset(mem, 0, MEMSIZE);

    if ((input = fopen(argv[2], "r")) == NULL) {
	perror("Can't open input file for reading");
	exit(1);
    }
    if ((output = fopen(argv[3], "w")) == NULL) {
	perror("Can't open output file for writing");
	exit(1);
    }

    contractually_obligate_emoter();

    ip = program;
    while (*ip) {
        ref = get_ref(*ip);
        if (ref >= 0) {
            op = ' ';
            advance_ip(&ip);
            if (is_op(*ip)) {
                op = *ip;
                advance_ip(&ip);
            }
            if (*ip == '=') {
                advance_ip(&ip);
                if (op == '@') {
                    val = find_label(program, *ip);
                    if (val < 0) {
                        die("undefined label", *ip);
                    }
                    mem[ref] = val;
                } else {
                    val = get_val(*ip);
                    mem[ref] = do_op(op, mem[ref], val);
                }
                ip++;
            } else if (*ip == '>') {
                fputc(mem[ref], output);
                ip++;
            } else if (*ip == '<') {
                mem[ref] = fgetc(input);
                ip++;
            } else if (*ip == '?') {
                advance_ip(&ip);
                val = get_val(*ip);
                advance_ip(&ip);
                op = *ip;
                advance_ip(&ip);
                val2 = get_val(*ip);

                if (op == '=') {
                    result = (val == val2);
                } else if (op == '>') {
                    result = (val > val2);
                } else if (op == '<') {
                    result = (val < val2);
                } else {
                    die("unimplemented relop", op);
                }
                {
                    int ix, ex, i;

                    for (ex = 0, i = 0; i < 26; i++) {
                        ex = (ex + mem[i]) % EMOTIONSIZE;
                    }
                    for (ix = 0, i = 0; i < 26; i++) {
                        ix += (mem[i] * 3) % INTENSITYSIZE;
                    }
                    ix %= INTENSITYSIZE;
                    emote(ex, ix);
                }
                if (result) {
                    ip = program + mem[ref];
                } else {
                    ip++;
                }
            } else {
                die("unimplemented operator", *ip);
            }
        } else if (is_whitespace(*ip)) {
            ip++;
        } else if (*ip == '(') {
            while (*ip != ')' && *ip != '\0') {
                ip++;
            }
            if (*ip == ')') {
                ip++;
            }
        } else if (*ip == ':') {
            ip += 2;
        } else {
            die("unimplemented instruction", *ip);
        }
    }

    return 0;
}
