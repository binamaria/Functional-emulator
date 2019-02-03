#include<stdio.h>

#define ADD	0
#define SUB	1
#define LOAD 2
#define STORE 3
#define JLEZ 4
#define JALR 5
#define HALT 7

unsigned char pc=0;
unsigned char r[4];
int main(void)
{
unsigned char program_inst[]={0xbf, 0xfe, 0x2b, 0x10, 0x90, 0xd1, 0xb1, 0xf4, 0x4e, 0x1f, 0x0d, 0x04, 0x10, 0x03, 0xb0, 0xf1, 0x1b, 0xb0, 0xf6, 0x5f, 0xbf, 0xff, 0x37, 0xb1, 0xf7,0x70};
unsigned char opcode;
unsigned char rd;
unsigned char rs;
unsigned char imm;
unsigned char temVal;
for(int i=0;i<4;i++)
{
	r[i]=0;
}
printf("size :: %d \n",sizeof(r[0]));
unsigned char memory[255];



memory[0xfe]=6;

unsigned char temp;
for(int i=0;i<300;i++)
{

	temp=program_inst[pc];
//	printf("%x \n",program_inst[i]);
	
	opcode=temp>>7;
	
	if(opcode==0)
	{
		opcode=temp>>4;
		if(opcode==ADD)
		{
			//s="ADD";
			
			rd=(temp>>2)&3;
		
			rs=(temp)&3;
		
			pc++;
			r[rd]=r[rd]+r[rs];
			printf("\n -- pc=%x  inst=%x  op=ADD A=%x B=%x C=%x D=%x\n",pc,temp,r[0],r[1],r[2],r[3]);
		}
		else if(opcode==SUB)
		{
			//s="SUB";
			rd=(temp>>2)&3;
			
			rs=(temp)&3;
		
			pc++;
			r[rd]=r[rd]-r[rs];
			printf("\n -- pc=%x  inst=%x  op=SUB A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
		}
		else if(opcode==LOAD)
		{	//s="LOAD";
			rd=(temp>>2)&3;
			
			rs=(temp)&3;
			
			pc++;
			r[rd]=memory[r[rs]];
			printf("\n -- pc=%x  inst=%x  op=LOAD A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
		}
		else if(opcode==STORE)
		{
			//s="STORE";
			rs=(temp)&3;
			rd=(temp>>2)&3;
		
			pc++;
			memory[r[rs]]=r[rd];
			printf("\n -- pc=%x  inst=%x  op=STORE A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
		}
		else if(opcode==JLEZ)
		{
			//s="JLEZ";
			rd=(temp>>2)&3;
			rs=(temp)&3;
			if(r[rs]==0)
			{
				pc=r[rd];
				printf("\n -- pc=%x  inst=%x  op=JLEZ A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
				
				
			}
			else{
			
				pc++;
			printf("\n -- pc=%x  inst=%x  op=JLEZ A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
	}
		}
		else if(opcode==JALR)
		{
			//s="JALR";
			rd=(temp>>2)&3;
			
			rs=(temp)&3;
			
			
			unsigned char x=pc+1;
			
			pc=r[rd];
			r[rs]=x+1;
			printf("\n -- pc=%x  inst=%x  op=JALR A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
		}
		else if(opcode==HALT)
		{
			
			printf("\n Value inside the memory FF is %u \n",r[0]);
			break;
		}
		
	}
	else if(opcode==1){
		opcode=temp>>6;
		if(opcode==2)
		{
			
			rd=(temp>>4)&3;
			
			imm=(temp)&15;

		r[rd]=(temp<<4)|(r[rd]&15);
		//	r[rd]=imm<<4;
			pc++;
			printf("\n -- pc=%x  inst=%x  op=LUI A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
			
		}
		else if(opcode==3)
		{
			//s="LLI";
			
			rd=(temp>>4)&3;
			
			imm=(temp)&15;
			
			r[rd]=(r[rd]&240)|imm;
			pc++;
			printf("\n -- pc=%x  inst=%x  op=LLI A=%x B=%x C=%x D=%x",pc,temp,r[0],r[1],r[2],r[3]);
		}
	
	}
	
}

	return 0;
	
}
