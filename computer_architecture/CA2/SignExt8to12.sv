module SignExt8to12(
    input[7:0] in,
    output[11:0] out);
    assign out = {in[7], in};
endmodule