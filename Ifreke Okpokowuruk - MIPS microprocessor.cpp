#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <cctype>
using namespace std;

string input[6]; //string array variable to hold user input
int pc = 40000000; //Program Counter
string registry[32]; //Register Files
string datamemory[128]; //Data Memory Files
string op; // String variable for op code
string rs, rt, address, rd, shamt, funct; // String variable for rest of I-type and R-type format

void showMenu();
string getInput();
void hex2binary(string &);
void decode(string &, string &, string &, string &, string &, string &, string &, string &);
void execute(string &, string &, string &, string &, string &, string &, string &, string &);
int btod(string);
string dtob(int);
string binExtend(string);
string bin2hex(string num);
int tc2d(string);
string d2tc(int);
string tcExtend(string);
string and(string, string);
string or(string, string);
string xor(string, string);


int main()
{
	string input[6]; //string variable to hold user input
	for(int i = 0; i < 32; i++)
	{
		registry[i] = "00000000";
	}
	for(int i = 0; i < 128; i++)
	{
		datamemory[i] = "00000000";
	}

	showMenu(); //Function to display commands
	for(int i = 0; i < 6; i++)
	{
		input[i] = getInput();
	}
	for(int i = 0; i < 6; i++)
	{
		
		cout << "\nPROGRAM COUNTER: " << pc;
		hex2binary(input[i]);
		decode(input[i], op, rs, rt, rd, shamt, funct, address);
		execute(input[i], op, rs, rt, rd, shamt, funct, address);
		pc += 1;
		cout << "\nPROGRAM COUNTER: " << pc << endl;
		system("pause");
	}
	
	for(int i = 0; i < 32; i++)
	{
		cout << endl << "REGISTER FILE "<< i+1 << ": " << registry[i] << endl;
	}
	system("pause");
	for(int i = 0; i < 128; i++)
	{
		cout << endl << "DATA MEMORY "<< i+1 << ": " << datamemory[i] << endl;
	}

	system("pause");
	return 0;
}

//Function to show Main Menu
void showMenu()
{
	cout << "\t\tWELCOME TO IFREKE'S MIPS MICROPROCESSOR!";
	cout << "\n\nPlease enter 6 consecutive MIPS instructions (8-bit Hexadecimal numbers): ";
	cout << "\nNOTE: DO NOT ENTER ANY LOWERCASE LETTERS. : ";
}

//FUNCTION THAT GETS USER INPUT AND VALIDATES IT
string getInput()
{
	string input;
	int i = 0;
	cin >> input; //Get user input

	//INPUT VALIDATION: Making sure the user enters valid hexadecimal digits 0-9, A-F
	while(input.length() > 8 || input.length() < 8)
	{
		cout << "Please enter no more than 8 bits, and no less than 8-bits: ";
		cin >> input;
	}
	for(i = 0; i < input.length(); i++)
	{
	while(input[i]!= '0' && input[i]!= '1' && input[i]!= '2' && input[i]!= '3' && input[i]!= '4' && input[i]!= '5' && input[i]!= '6' && input[i]!= '7' && input[i]!= '8' && input[i]!= '9' && input[i]!= 'A' && input[i]!= 'B' && input[i]!= 'C' && input[i]!= 'D' && input[i]!= 'E' && input[i]!= 'F')
	{
		cout << "Please enter valid hexadecimal digits. ";
		cout << "\nRe-enter your 8-bit hexadecimal number: ";
		cin >> input;
		i = 0;
	}
	}
	return input;
}

//FUNCTION THAT TAKES USER'S HEXIDECIMAL INPUT AND TURNS IT TO BINARY STRING
void hex2binary(string &input)
{
	string temp;
	for(int i = 0; i < 8; i++)
	{
		if(input[i] == '0')
			temp.append("0000");
		else if(input[i] == '1')
			temp.append("0001");
		else if(input[i] == '2')
			temp.append("0010");
		else if(input[i] == '3')
			temp.append("0011");
		else if(input[i] == '4')
			temp.append("0100");
		else if(input[i] == '5')
			temp.append("0101");
		else if(input[i] == '6')
			temp.append("0110");
		else if(input[i] == '7')
			temp.append("0111");
		else if(input[i] == '8')
			temp.append("1000");
		else if(input[i] == '9')
			temp.append("1001");
		else if(input[i] == 'A')
			temp.append("1010");
		else if(input[i] == 'B')
			temp.append("1011");
		else if(input[i] == 'C')
			temp.append("1100");
		else if(input[i] == 'D')
			temp.append("1101");
		else if(input[i] == 'E')
			temp.append("1110");
		else if(input[i] == 'F')
			temp.append("1111");
	}
	input = temp;
}

//FUNCTION THAT DECODES BINARY STRING AND DECIDES WHAT TYPE OF INSTRUCTION IT IS
void decode(string &input, string &op, string &rs, string &rt, string &rd, string &shamt, string &funct, string &address)
{
	op = input.substr(0, 6);
	if (op  == "000000")
	{
		rs = input.substr(6, 5);
		rt = input.substr(11, 5);
		rd = input.substr(16, 5);
		shamt = input.substr(21, 5);
		funct = input.substr(26, 6);
	}else if(op == "100011")
	{
		rs = input.substr(6, 5);
		rt = input.substr(11, 5);
		address = input.substr(16, 16);
	}else if(op == "101011")
	{
		rs = input.substr(6, 5);
		rt = input.substr(11, 5);
		address = input.substr(16, 16);
	}else if(op == "001000")
	{
		rs = input.substr(6, 5);
		rt = input.substr(11, 5);
		address = input.substr(16, 16);
	}else if(op == "000100")
	{
		rs = input.substr(6, 5);
		rt = input.substr(11, 5);
		address = input.substr(16, 16);
	}else if(op == "000101")
	{
		rs = input.substr(6, 5);
		rt = input.substr(11, 5);
		address = input.substr(16, 16);
	}
}

//FUNCTION TO EXECUTE ALU OPERATIONS
void execute(string &input, string &op, string &rs, string &rt, string &rd, string &shamt, string &funct, string &address)
{
	int temp1, temp2, temp3; //temporary variable holders
	int tempop = btod(op), temprs = btod(rs), temprt = btod(rt), temprd = btod(rd), tempShamt = btod(shamt), tempFunct = btod(funct), tempAdd = tc2d(address);
	if (op  == "000000")
	{
		if (funct == "100000")
		{
			// ADD INSTRUCTION
			cout << "\nThe instruction is add $" << btod(rd) << ", $" << btod(rs) << ", $" << btod(rt) << endl;
			hex2binary(registry[temprd - 1]);
			hex2binary(registry[temprs - 1]);
			hex2binary(registry[temprt - 1]);
			temp1 = tc2d(registry[temprd - 1]);
			temp2 = tc2d(registry[temprs - 1]);
			temp3 = tc2d(registry[temprt - 1]);
			temp1 = temp2 + temp3;
			registry[temprd-1] = d2tc(temp1);
			registry[temprd-1] = tcExtend(registry[temprd-1]);
			registry[temprd-1] = binExtend(registry[temprd-1]);
			registry[temprd-1] = bin2hex(registry[temprd-1]);
			cout << "REGISTER " << temprs << ": " << bin2hex(registry[temprs-1] ) << " H" << endl;
			cout << "REGISTER " << temprt << ": " << bin2hex(registry[temprt-1] ) << " H" << endl;
			cout << "REGISTER " << temprd << ": " << registry[temprd-1] << " H" << endl;
			registry[temprs-1] = bin2hex(registry[temprs-1]);
			registry[temprt-1] = bin2hex(registry[temprt-1]);
		}else if(funct == "100010")
		{
			// SUBTRACT INSTRUCTION
			cout << "\nThe instruction is sub $" << btod(rd) << ", $" << btod(rs) << ", $" << btod(rt) << endl;
			hex2binary(registry[temprd - 1]);
			hex2binary(registry[temprs - 1]);
			hex2binary(registry[temprt - 1]);
			temp1 = tc2d(registry[temprd - 1]);
			temp2 = tc2d(registry[temprs - 1]);
			temp3 = tc2d(registry[temprt - 1]);
			temp1 = temp2 - temp3;
			registry[temprd-1] = d2tc(temp1);
			registry[temprd-1] = tcExtend(registry[temprd-1]);
			registry[temprd-1] = binExtend(registry[temprd-1]);
			registry[temprd-1] = bin2hex(registry[temprd-1]);
			cout << "REGISTER " << temprs << ": " << bin2hex(registry[temprs-1] ) << " H" << endl;
			cout << "REGISTER " << temprt << ": " << bin2hex(registry[temprt-1] ) << " H" << endl;
			cout << "REGISTER " << temprd << ": " << registry[temprd-1] << " H" << endl;
			registry[temprs-1] = bin2hex(registry[temprs-1]);
			registry[temprt-1] = bin2hex(registry[temprt-1]);
		}else if(funct == "100100")
	{
		// AND INSTRUCTION
		cout << "\nThe instruction is and $" << btod(rd) << ", $" << btod(rs) << ", " << btod(rt) << endl;
		hex2binary(registry[temprs - 1]);
		hex2binary(registry[temprt - 1]);
		registry[temprd - 1] = and(registry[temprs - 1], registry[temprt - 1]);
		registry[temprd-1] = bin2hex(registry[temprd-1]);
		cout << "REGISTER " << temprs << ": " << bin2hex(registry[temprs-1] ) << " H" << endl;
		cout << "REGISTER " << temprt << ": " << bin2hex(registry[temprt-1] ) << " H" << endl;
		cout << "REGISTER " << temprd << ": " << registry[temprd-1] << " H" << endl;
		registry[temprs-1] = bin2hex(registry[temprs-1]);
		registry[temprt-1] = bin2hex(registry[temprt-1]);
	}else if(funct == "100101")
	{
		// OR INSTRUCTION
		cout << "\nThe instruction is or $" << btod(rd) << ", $" << btod(rs) << ", " << btod(rt) << endl;
		hex2binary(registry[temprs - 1]);
		hex2binary(registry[temprt - 1]);
		registry[temprd - 1] = or(registry[temprs - 1], registry[temprt - 1]);
		registry[temprd-1] = bin2hex(registry[temprd-1]);
		cout << "REGISTER " << temprs << ": " << bin2hex(registry[temprs-1] ) << " H" << endl;
		cout << "REGISTER " << temprt << ": " << bin2hex(registry[temprt-1] ) << " H" << endl;
		cout << "REGISTER " << temprd << ": " << registry[temprd-1] << " H" << endl;
		registry[temprs-1] = bin2hex(registry[temprs-1]);
		registry[temprt-1] = bin2hex(registry[temprt-1]);
	}else if(funct == "100110")
	{
		// XOR INSTRUCTION
		cout << "\nThe instruction is xor $" << btod(rd) << ", $" << btod(rs) << ", " << btod(rt) << endl;
		hex2binary(registry[temprs - 1]);
		hex2binary(registry[temprt - 1]);
		registry[temprd - 1] = xor(registry[temprs - 1], registry[temprt - 1]);
		registry[temprd-1] = bin2hex(registry[temprd-1]);
		cout << "REGISTER " << temprs << ": " << bin2hex(registry[temprs-1] ) << " H" << endl;
		cout << "REGISTER " << temprt << ": " << bin2hex(registry[temprt-1] ) << " H" << endl;
		cout << "REGISTER " << temprd << ": " << registry[temprd-1] << " H" << endl;
		registry[temprs-1] = bin2hex(registry[temprs-1]);
		registry[temprt-1] = bin2hex(registry[temprt-1]);
	}
	}else if(op == "100011")
	{
		// LOAD WORD INSTRUCTION
		cout << "\nThe instruction is lw $" << btod(rt) << ", " << tc2d(address) << "($" << btod(rs) << ")" << endl;
		if ((tempAdd + temprs) > 128)
			cout << "Error: Not enough data memory allocations for this instruction. \n";
		else
		{
			registry[temprt - 1] = datamemory[(temprs + tempAdd) - 1];
			cout << "DATA MEMORY FILE " << temprs + tempAdd << ": " << datamemory[(temprs + tempAdd) - 1] << " H" << endl;
			cout << "REGISTER " << temprt << ": " << registry[temprt-1] << " H" << endl;
		}
	}else if(op == "101011")
	{
		// STORE WORD INSTRUCTION
		cout << "\nThe instruction is sw $" << btod(rt) << ", " << tc2d(address) << "($" << btod(rs) << ")" << endl;
		if ((tempAdd + temprs) > 128)
			cout << "Error: Not enough data memory allocations for this instruction. \n";
		else
		{
			datamemory[(temprs + tempAdd) - 1] = registry[temprt - 1];
			cout << "REGISTER " << temprt << ": " << registry[temprt-1] << " H" << endl;
			cout << "DATA MEMORY FILE " << temprs + tempAdd << ": " << datamemory[(temprs + tempAdd) - 1] << " H" << endl;
		}
	}else if(op == "001000")
	{
		// ADD IMMEDIATE INSTRUCTION
		cout << "\nThe instruction is addi $" << btod(rt) << ", $" << btod(rs) << ", " << tc2d(address) << endl;
		hex2binary(registry[temprt - 1]);
		hex2binary(registry[temprs -1]);
		temp1 = btod(registry[temprt - 1]);
		temp2 = btod(registry[temprs - 1]);
		temp1 = temp2 + tempAdd;
		registry[temprt-1] = d2tc(temp1);
		registry[temprt-1] = tcExtend(registry[temprt-1]);
		registry[temprt-1] = binExtend(registry[temprt-1]);
		registry[temprt-1] = bin2hex(registry[temprt-1]);
		cout << "REGISTER " << temprs << ": " << bin2hex(registry[temprs-1]) << " H" << endl;
		cout << "REGISTER " << temprt << ": " << registry[temprt-1] << " H" << endl;
		registry[temprs-1] = bin2hex(registry[temprs-1]);
	}else if(op == "000100")
	{
		// BRANCH ON EQUAL INSTRUCTION
		cout << "\nThe instruction is beq $" << btod(rs) << ", $" << btod(rt) << ", " << btod(address) << endl;
		if(	(registry[temprs-1]) == (registry[temprt-1]))
		{
			pc += tempAdd-1;
		}
	}else if(op == "000101")
	{
		// BRANCH ON NOT EQUAL INSTRUCTION
		cout << "\nThe instruction is bne $" << btod(rs) << ", $" << btod(rt) << ", " << btod(address) << endl;
		if(	(registry[temprs-1]) != (registry[temprt-1]))
		{
			pc += tempAdd-1;
		}
	}
}

//Function to convert binary numbers to decimal
int btod(string number)
{
	int result = 0, power = 0;
	for(int i = number.length()-1; i >= 0; i--)
	{
		result += (number[i]-'0')*pow(2.0, power++);
	}
	return result;		
}

//FUNCTION THAT CONVERTS DECIMAL TO BINARY
string dtob(int num)
{
	if(num == 0) return "0";
	if(num == 1) return "1";

	if(num %2 == 0)
		return dtob(num /2) + "0";
	else
		return dtob(num/2) + "1";
}

//FUNCTION THAT SIGN EXTENDS TWO'S COMPLEMENT BINARY NUMBER
string binExtend(string num)
{
	int i2 = 32 - num.length();
	if(num[0] == '0')
	{
		for(int i = 0; i < i2; i++)
		{
			num = "0" + num;
		}
	}else if(num[0] == '1')
	{
		for(int i = 0; i < i2; i++)
		{
			num = "1" + num;
		}
	}
	return num;
}

//FUNCTION THAT CONVERTS BINARY NUMBER TO HEXADECIMAL
string bin2hex(string num)
{
	string temp, holder;
	for(int i = 0; i < 32; i+= 4)
	{
		temp = num.substr(i, 4);
		if(temp == "0000")
			holder += "0";
		else if (temp == "0001")
			holder += "1";
		else if (temp == "0010")
			holder += "2";
		else if (temp == "0011")
			holder += "3";
		else if (temp == "0100")
			holder += "4";
		else if (temp == "0101")
			holder += "5";
		else if (temp == "0110")
			holder += "6";
		else if (temp == "0111")
			holder += "7";
		else if (temp == "1000")
			holder += "8";
		else if (temp == "1001")
			holder += "9";
		else if (temp == "1010")
			holder += "A";
		else if (temp == "1011")
			holder += "B";
		else if (temp == "1100")
			holder += "C";
		else if (temp == "1101")
			holder += "D";
		else if (temp == "1110")
			holder += "E";
		else if (temp == "1111")
			holder += "F";
	}
	return holder;
}

//FUNCTION THAT CONVERTS TWO'S COMPLEMENT TO DECIMAL
int tc2d(string num)
{
	int power = 0, dec = 0;
	if(num[0] == '0')
	{
		for(int i = num.length() - 1; i >= 0; i--)
		{
			dec += (num[i]-'0')*(pow(2.0, power++));
		}
		return dec;
	}else if(num[0] = '1')
	{
		//Take result and flip every number
		for(int i = num.length() - 1; i >= 0; i--)
		{
			if(num[i] == '0')
				num[i] = '1';
			else
				num[i] = '0';
		}

		//Convert flipped number to decimal
		power = 0, dec = 0; 
		for(int i = num.length() - 1; i >= 0; i--)
		{
			dec += ((num[i]-'0')*pow(2.0, power++));
		}

		//Subtract 1 from decimal
		dec += 1;

		//Put a negative sign in front of the decimal #
		return (dec)*(-1);
	}
}

//FUNCTION THAT CONVERTS DECIMAL TO TWO'S COMPLEMENT
string d2tc(int num)
{
	if(num == 0)
	{
		return "00000000";
	}else if (num > 0)
	{
		return dtob(num);
	}else
	{
		string holder;
		num = num*(-1); //flip sign
		num -= 1; //minus one
		holder = dtob(num); //decimal to binary
		holder = tcExtend(holder); //two's complement extend
		for(int i = holder.length() - 1; i >= 0; i--) //flip every number
		{
			if(holder[i] == '0')
				holder[i] = '1';
			else
				holder[i] = '0';
		}
		return holder;
	}
}

//FUNCTION THAT MAKES ANY BINARY NUMBER A TWO'S COMPLEMENT NUMBER
string tcExtend(string num)
{
	if(num.length()%4 == 3)
		return "0" + num;
	else if(num.length()%4 == 2)
		return "00" + num;
	else if(num.length()%4 == 1)
		return "000" + num;
	else
		return num;
}

//FUNCTION THAT EXECUTES AND INSTRUCTION
string and(string num, string num1)
{
	string result;
	for(int i = num.length()-1; i >= 0; i--)
	{
		if((num[i] == '1') && (num1[i] == '1'))
			result = '1' + result;
		else
			result = '0' + result;
	}
	return result;
}

//FUNCTION THAT EXECUTES OR INSTRUCTION
string or(string num, string num1)
{
	string result;
	for(int i = num.length()-1; i >= 0; i--)
	{
		if((num[i] == '1') && (num1[i] == '1'))
			result = '1' + result;
		else if((num[i] == '0') && (num1[i] == '1'))
			result = '1' + result;
		else if((num[i] == '1') && (num1[i] == '0'))
			result = '1' + result;
		else
			result = '0' + result;
	}
	return result;
}

//FUNCTION THAT EXECUTES XOR INSTRUCTION
string xor(string num, string num1)
{
	string result;
	for(int i = num.length()-1; i >= 0; i--)
	{
		if((num[i] == '0') && (num1[i] == '1'))
			result = '1' + result;
		else if((num[i] == '1') && (num1[i] == '0'))
			result = '1' + result;
		else
			result = '0' + result;
	}
	return result;
}