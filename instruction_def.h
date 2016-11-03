

typedef enum
{
	R_TYPE, I_TYPE, S_TYPE, SB_TYPE, U_TYPE, UJ_TYPE, NOT_DEFINED
}INSTYPE;

INSTYPE opToINSTYPE(int op)
{
	switch(op)
	{
		case 0x33: // b0110011
			return R_TYPE;
		
		case 0x67: // b1100111
		case 0x03: // b0000011
		case 0x13: // b0010011
		case 0x73: // b1110011
			return I_TYPE;
		
		case 0x23: // b0100011 
			return S_TYPE;
		
		case 0x63: // b1100011
			return SB_TYPE;
		
		case 0x37: // b0110111
		case 0x17: // b0010111
			return U_TYPE;
	
		case 0x6F: // b1101111
			return UJ_TYPE;
		
		default:
			return NOT_DEFINED;
	}
}


