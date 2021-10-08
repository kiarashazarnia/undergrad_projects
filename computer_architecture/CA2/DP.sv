module DP(
		input clk, rst,
		input sel_imm, store, en, pop, push, sh_o_ALU, R2_o_Rd, regWrite,
		input [1:0] pc_state, what_the_faz,
		output C_out, Z_out,
		output[4:0] command
);

    logic[18:0] eighteen;
    logic[11:0] one,two,fourteen,fifteen,sixteen,seventeen, twentyfive;
    logic[2:0] four,five,six, twentyseven;
    logic[7:0] three,seven,eight,nine,ten,eleven,twelve,thirteen, twentysix;
    logic nineteen, twenty, twentyone, twentytwo, twentythree, twentyfour;


	assign command = eighteen[18:14];

	always_comb begin
		two = eighteen[11:0];
		three = eighteen[7:0];
		four = eighteen[7:5];
		five = eighteen[10:8];
		six = eighteen[13:11];
	end

    InsMemory InsMemory_u(one, eighteen);
	/*input[11:0]  address,
	output[18:0]  ins_out);*/

    RegisterFile RegisterFile_u( clk, rst, five, four, six, twelve, regWrite, seven, eight);
	/*input clk,
	input rst,
	input[2:0]  reg1,
	input[2:0]  reg2,
	input[2:0]  regw,
	input[7:0]  write,
	input       regWrite,**********************contr
	output[7:0] read1,
	output[7:0] read2);*/

    mux2x8bit mux2x8bit_u1( eight, three, sel_imm, nine);
	/*input[7:0]  a,
	input[7:0]  b,
	input       sel,****************************Cont
	output[7:0] c
);*/

    ALU ALU_u( seven, nine, eighteen[16:14], C_out, twentyone, nineteen, ten);
	/*input[7:0]  a,
	input[7:0]  b,
	input[2:0]  fn,
	input       carryIn,
	output ALU_Z,
	output logic    ALU_C,
	output logic [7:0] out);*/

    DataMem DataMem_u( clk, twentysix, eight, store, eleven);
    /*input clk,
    input[7:0] address,
    input[7:0] data,
    input store,******************************CONt
    output logic[7:0] out);*/

    PC PC_u( clk, rst, fifteen, one);
	/*input        clk,
	input        rst,
	input[11:0]  pcIn,
	output logic[11:0] pcOut);*/

    FF C_u( clk, rst, en, twentythree, C_out);
	/*input        clk,
	input        rst,
    input        en,****************CONT
	input        in,
	output logic out);****************PRIMARY OUT CONT*/

    FF Z_u( clk, rst, en, twentyfour, Z_out);
	/*input        clk,
	input        rst,
    input        en,
	input        in,
	output logic out);*/

    Adder12 adder12_u( fourteen, sixteen, seventeen);
    /*input [11:0]a,b,
    output w);*/

    PCAdd1 Pcadd1_u( one, fourteen);
	/*input[11:0]  pcIn,
	output[11:0] pcOut
);*/
    shifter sh_u(eighteen[15:14], four, seven, twenty, twentytwo, thirteen);
    /*input[1:0] fn,
    input[2:0] shiftCount,
    input[7:0] in,
    output logic shiftC,
    output shiftZ,
    output logic[7:0] out
);*/
    SignExt8to12 signext_u(three, sixteen);
    /*input[7:0] in,
    output[11:0] out);*/
    stack stack_u(clk, rst, pop, push, fourteen, twentyfive);
	/*input        clk, rst,
	input        pop,****************CONT
	input        push,***********CONT
	input[11:0]  inp,
	output logic[11:0] out);*/

    mux2x1bit mux_C(nineteen, twenty, sh_o_ALU, twentythree);
/*	input a,
	input b,
	input sel,*********CONT
	output c
);*/
    mux2x1bit mux_u1(twentyone, twentytwo, sh_o_ALU, twentyfour);

    mux4x12bit mux_u2(fourteen, twentyfive, two, seventeen, pc_state, fifteen);
	/*input[11:0]  a,
	input[11:0]  b,
	input[11:0]  c,
	input[11:0]  d,
	input[1:0]   sel,*********************CONT
	output logic[11:0] e
);*/

    mux4x8bit mux_u3( ten, eleven, thirteen, thirteen, what_the_faz, twelve);
/*	input[7:0]  a,
	input[7:0]  b,
	input[7:0]  c,
	input[7:0]  d,
	input[1:0]  sel,*******************CONT
	output logic[7:0] e
);*/

	always_comb	twentysix = three + seven;
	always_comb twentyseven = R2_o_Rd? six : five;

endmodule
