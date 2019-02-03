//This is a partially completed risc processor
//only the ADD LUI and HALT instructions are done.
//can you fill in the rest?
//
//you can get verilog from http://www.swarthmore.edu/NatSci/mzucker1/e15/iverilog-instructions.html
//
//if you have icarus verilog installed you can compile and run it as so:
//iverilog -o myrisc.vvp -v myrisc.v
//vvp myrisc.vvp
//
//otherwise, go to http://www.iverilog.com/ and paste it in
//
//CAUTION: don't run this program as-is.  It will just hang-up.  Put in the other instructions first!

`define ADD	4'd0
`define SUB	4'd1
`define LOAD	4'd2
`define STORE	4'd3
`define JLEZ	4'd4
`define JALR	4'd5
`define HALT	4'd7
`define LUI	2'd2
`define LLI	2'd3

`define OPCODE_4	7:4	//opcode
`define	OPCODE_2	7:6	//opcode for LLI LUI
`define INST_RS		1:0
`define INST_RD		3:2
`define INST_RT		5:4
`define INST_IMM	3:0	//4-bit immediate

module RiSC ();
	reg	clk=0;

	reg [7:0] r[0:3];	//4 registers A; m[0]=B; m[0]=C; m[0]=D
	reg [7:0] pc;		//program counter
	reg [7:0] m[0:255];	//memory

	wire [7:0] inst;	//quick access to the current instruction
	
	//the current instruction is set to be the memory contents at pc
	assign inst=m[pc];

	initial begin
		$display("starting...");

		pc=0;		//set all the registers to 0
		r[0]=0;
		r[1]=0;
		r[2]=0;
		r[3]=0;

		//load the multiply by 3 test program
		m[0]=8'hbf; m[1]=8'hfe; m[2]=8'h23; m[3]=8'h15; m[4]=8'ha0; m[5]=8'he3; m[6]=8'hb1; m[7]=8'hf0; m[8]=8'h4e; 
		m[9]=8'h04; m[10]=8'hb0; m[11]=8'hf1; m[12]=8'h1b; m[13]=8'hb0; m[14]=8'hf6; m[15]=8'h5f; 
		m[16]=8'hbf; m[17]=8'hff; m[18]=8'h37; m[19]=8'h70;

		m[254]=2;	//memory[FE] is 2

		//TODO: once you have the times three test program running, put your fibonacci here instead
		//note: make the last instruction of your program HALT instead of infinite loop.
		// the instruction is 8'h70
	end

	always
		#1 clk=~clk;	//every 1 time unit, flip the clock.

	//instructions are executed on the positive clock edge
	always @(posedge clk) begin
		//handle add; sub, load store jalr jlez
		case (inst[`OPCODE_4])
	
			`ADD:	begin
				r[inst[`INST_RD]]<=r[inst[`INST_RD]]+r[inst[`INST_RS]];
				pc<=pc+1;

				$display("PC=%h, inst=%h, op=ADD, A=%h, B=%h, C=%h, D=%h",pc,inst,r[0],r[1],r[2],r[3]);
				end

			//TODO: put your code here


			`HALT:	begin
				$display("PC=%h, inst=%h, op=HALT, A=%h, B=%h, C=%h, D=%h",pc,inst,r[0],r[1],r[2],r[3]);
				$display("Memory[FF]=%h",m[255]);
				$finish;
				end

		endcase
		case (inst[`OPCODE_2])
	
			`LUI:	begin
				r[inst[`INST_RT]]<={inst[`INST_IMM],r[inst[`INST_RT]][3:0]};
				pc<=pc+1;

				$display("PC=%h, inst=%h, op=LUI, A=%h, B=%h, C=%h, D=%h",pc,inst,r[0],r[1],r[2],r[3]);
				end

			//TODO: put your code here

		endcase


	end
endmodule
