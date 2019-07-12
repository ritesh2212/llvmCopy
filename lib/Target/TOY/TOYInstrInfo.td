include "TOYInstrFormats.td"

def ADDrr : InstTOY<(outs GRRegs:$dest),
 (ins GRRegs:$src1, GRRegs:$src2),
 "add $dest, $src1,$src2",
[(set i32:$dest, (add i32:$src1, i32:$src2))]>;

