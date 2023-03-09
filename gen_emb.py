#!python3
import yaml

import sys
import argparse

def camel_to_uppercase(s: str):
    prev = s[0]
    res = prev.upper()
    for c in s[1:]:
        if c.isupper() and prev.islower():
            res += "_"
        res += c.upper()
        prev = c
    return res

def main():
    parser = argparse.ArgumentParser(
        prog="gen_emb", description="Simple generator for the embedded files"
    )

    parser.add_argument("-i", "--input", default="../jabus_impl_gen.cmds", help="file that defines the commands")

    args = parser.parse_args()

    commands = []
    y = yaml.load(open(args.input, "rt").read(), Loader=yaml.Loader)
    commands = y["cmds"]



    # with open(args.input,"rt") as fh:
    #     for l in fh:
    #         l = l.strip()
    #         if not l:
    #             continue
    #         l = l.split()[0]    # only care about first word
    #         if not l or l[0]=="#":
    #             continue
    #         commands.append(l)

    print ("Commands:")
    for c in commands:
        print ("*", c)

    out_fn = args.input.replace(".yaml",".c")
    if out_fn == args.input:
        raise Exception()

    print (f"Generate {out_fn}:")
    with open(out_fn,"wt", newline="\n") as fh:
        fh.write("""// Autogen

struct Cmd2FuncItem
{
    uint16_t cmd;
    uint8_t req_length; // raw length byte, ie can have bit 7 set. Note that bit0..6 inidcates complete packet size (except preamble and extended data)
    uint8_t ans_length;
    int (*func)(struct JabusContext *context, union JabusCommands *pkt);
};
""")
        for c in commands:
            uc = camel_to_uppercase(c)
            fh.write(f"#define IMPLEMENT_{uc}\n")
            fh.write(f"static inline int func{c}(struct JabusContext *context, struct JabusRequest{c} *pkt);\n")
            fh.write(f"static int _func{c}(struct JabusContext *context, union JabusCommands *pkt) {{ return func{c}(context, &pkt->req{c}); }}\n\n")

        fh.write(f"#define NUM_CMD_FUNCS {len(commands)}\n")
        fh.write("static const struct Cmd2FuncItem cmd2funcs[NUM_CMD_FUNCS] =\n{\n")
        for c in commands:
            uc = camel_to_uppercase(c)
            a = f"{'JabusRequest'+c:30s}"
            b = f"{'JabusAnswer'+c:30s}"
            fh.write(f"  {{ JABUS_CMD_{uc:30s}, sizeof(struct {a}), sizeof(struct {b}), _func{c} }},\n")
            uc = camel_to_uppercase(c)
        fh.write("};\n")


main()
