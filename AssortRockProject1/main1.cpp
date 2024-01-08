//����Ű
// Ctrl + k,c : ������ �ּ�����
// Ctrl + k,u : ������ �ֽ�����
// Alt + Drag
// ����� : F5(n�� ������ n�� �ߴ������� ����), F9(�ߴ�������,������������), F10(�������, ��������), F11(�������, ��������), shift + F5(���������)


#include <stdio.h>

#define HUNGRY  0x1 
#define THIRSTY 0x2
#define TIRED   0x4
#define FIRE	0x8

#define COLD	0x10
#define POISON	0x20
#define POISON1	0x30
#define POISON2	0x40

#define POISON3	0x100 
#define POISON4	0x200
#define POISON5	0x300
#define POISON6	0x800
//��ó������� ���ؼ� ������+���������� ������ ���� �� �ִ�.��Ʈ�� ĭ�̱� ������ 2�� ����� ����
//0x 16����ǥ���ǹ�

//����
//��������(�Լ���), ��������, ��������(3����), �ܺκ���(������ ��)

int global = 0;//��������(�Լ����� ����)

int Add1(int left, int right)
{
	return left + right;
}

int Factorial(int _oNum)
{
	int oValue = 1;

	for (int j = 0; j < _oNum - 1; ++j)
	{
		oValue *= (j + 2);
	}

	return oValue;
}

//����Լ�(Recursion) : ������ ���� ������ ����, �ݵ�� Ż�ⱸ�� �־����, ���� ť Ȱ���ؼ� �ݺ������ε� ��������
//����Լ� ���� ���丮��
int Factorial_Re(int _oNum)
{
	if (1 == _oNum)
	{
		return 1;
	}

	return _oNum * Factorial_Re(_oNum - 1);

}

//�Ǻ���ġ���� 1 1 2 3 5 8 13 21 34 55...
int Fibonacci(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}

	int oPrev1 = 1;
	int oPrev2 = 1;
	int oValue = 0;

	for (int i = 0; i < _iNum - 2; ++i)
	{
		oValue = oPrev1 + oPrev2;
		oPrev1 = oPrev2;
		oPrev2 = oValue;

	}

	return oValue;
}

//����Լ� ���� �Ǻ���ġ ���� >> �������¹��� ���� ��� �� ��� Ȱ��
int Fibonacci_Re(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}

	return Fibonacci_Re(_iNum - 1) + Fibonacci_Re(_iNum - 2);
}


//����������ڷ��� (c��Ÿ�Ϸ�)
typedef struct _tagMyST
{
	int a;
	float f;
}MYST;

typedef struct _tagBig
{
	MYST k;
	int i;
	float c;
}BIG;

typedef int INT;

typedef struct NewStruct
{
	int a;
	short s;
}NEWST;


//�Լ�(���,Function)
int main()
{
	//�ڷ���DataType : ������ >> unsigned(�����) + char(1),short(2),int(4),long(4),long long(8)/ �Ǽ��� >> float(4),double(8)
	//1Byte == 8bit == 2^8 == 256���, ��int == 4Byte == 32Bit == 1024��� == 2^10 == 1KB
	//KB < MB < GB < TB ��1024�辿 ����
	// = �� ������ �ǹ�, == ������ �ǹ�
	int i = 0; 	//int : �ڷ���, i : ���Ǻ���

	//������ ǥ��� ���� >> ������ ����, ������ �������� ����Ͽ� ����� ������ ������ ������ ������ 
	//�޸𸮸� 0���� ������ִ� �����+������ȣ(MSB,Most Significant Bit)�� ǥ��, [2�� ������]
	unsigned char c = 0;
	c = 0;
	c = 255;
	c = -1; //�޸𸮻��´� ������ unsigned char������ 255�� ����

	signed char c1 = 0;
	c1 = -128;
	c1 = 127;
	c1 = 255; //�޸𸮻��´� ������ signed char������ -1�� ����,  
	
	//�Ǽ��� �����ʹ� [�ε��Ҽ���] ������� ǥ��, MSB+������Ʈ+������Ʈ, ���е��� ���� �ٻ簪���� ǥ��
	//�Ǽ�ǥ���ڿ� f�� ���̸� floatŸ��, �Ⱥ��̸� doubleŸ�� ����

	//�����ʹ� ���� ������ ������ ��Ģ, ���� ���� ��ȯ�� ���
	float f = 10.2415f + float(20);

	//������ : {��������� + - * / %(��ⷯ��,������)} {���������� ++ -- } {���Կ����� = }
	//�켱���� : x++ x--, ++x --x, * /, + -, << >>, < <= > >=, == !=, ��ƮAND���� &, ��ƮXOR���� ^, ��ƮOR���� |, && , ||, ?:, ���Կ���
	int data = 10 + 10;
	data + 20; //���길�ϰ� ����x
	data += 20; //data = data + 20;

	//�Ǽ��� �����ʹ� %��ⷯ�� ������ �Ұ�
	
	//���������ڴ� '�Ѵܰ� ����/����'�� ����, ��/�ڿ� ��ġ�Ͽ� ����(��ġ)/����(��ġ) ��������� �ֿ켱 Ȥ�� ���ļ����� �����ټ� ����
	data = 0;
	int a;
	a = 10;
	data=++a;
	data=a++;

	//�� ������(true/false) : !(��), &&(��), ||(��)
	//True == 0�� �ƴ� ��
	//bool �� �������� ���� 1byte �ڷ���
	bool turefalse = false; //==0
	bool IsTrue = 100; //==1

	IsTrue = true;
	IsTrue = !IsTrue;

	int iTrue = 0;
	iTrue = !iTrue;

	iTrue = 0 && 200;
	iTrue = 0 || 300;
	iTrue = 0 || 0;

	//�� ������ : ==. !=, <, >, <=, >=, 


	//���� if_else if_else, switch case
	data = 0;

	if (100 && 200)
	{
		data = 100;
	}
	else if (300)
	{
		
	}
	else if (400)
	{
	
	}
	else //�����뼱(�پȵǸ� ���ళ��), �����
	{
	
	}

	int iTest = 20;
	switch (iTest) //�ڵ尡 �� �� ����, ����� ���� ���������� �����ϰ� ������(if������ �������ڽ����)
	{
	case 10:
	case 20:
	case 30:
		break; //�ǵ��� ���� �ƴ϶�� ¦ �� �������
	case 40:
			break;
	default: //else����
		break;
	}

	//same-ex
	if (iTest == 10 || iTest == 20 || iTest == 30)
	{

	}
	else if (true)
	{

	}
	else
	{

	}

	//���� ������ :?
	// ~~~? ������ : ��������
	iTest == 20 ? iTest = 100 : iTest == 200; // == �����Ƿν� ���������� �ƴϳ� ���������� ��������Ե�

	if (iTest==20)
	{
		iTest = 100;
	}
	else
	{
		iTest == 200;
	}

	//��Ʈ ������, ��Ʈ������ ����� << >>(����Ʈ:��Ʈ�� ��ĭ�� �б�), &(��) |(��) ^(XOR:������0,�ٸ���1) ~(��)
	unsigned char byte = 1;
	byte << 1; //1������, ��길�ϰ� ������ ����
	byte <<= 3; //3������ 1�� 8�̵�
	byte >>= 1; //1�°��� 8�� 4����

	unsigned int iStatus = 0; 
	
	//���� �߰�
	iStatus |= HUNGRY; 	//��ó�� ����, ������� �߰�
	iStatus |= THIRSTY; //�̹� ����Ŀ��� �񸶸��� ��Ʈ�������� ���ļ� ����


	//���� Ȯ��
	if (iStatus & THIRSTY) //�Ѵ� 1�϶��� ��
	{

	}

	//���� ����
	iStatus &= ~THIRSTY; //������0 ����, Ư�� �ڸ� ��Ʈ ����

	data = Add1(10, 20);


	//�ݺ��� : for(), while(), ���α׷� ��ӽ���/���Ḧ ��Ʈ��


	int iData = Add1(100, 200);

	//for (/*�ݺ��� �ʱ�ȭ*/; /*�ݺ��� ����üũ*/; /*�ݺ��� ����(Ż�⿩��)*/)
	for (int i = 0; i < 4; ++i)
	{
		if (i % 2 == 1)
		{
			continue; //�� ��ɾ��� ó������ �ٽ�, break�� �ߴ��� �����ܰ��
		}
		printf("Output Test\n");

	}

	int j = 0;
	while (j < 2)
	{
		printf("Output Test\n");
		++j;
	}


	//�ܼ� : �����â �̶�� ��
	printf("abcdef %d \n", 10);		//������ %d
	printf("abcdef %f \n", 3.14f);	//�Ǽ��� %f, ������Ÿ���� float�� ����

	for (int i = 0; i < 10; ++i)
	{
		printf("Output i : %d \n", i);
	}

	//scanf ���� �Է¹ޱ�
	int iInput = 0;
	scanf_s("%d", &iInput);

	//�ڷᱸ��, �����Ͱ���
	//���� : ��������, ���Լ��� >> �Լ��� ����ϴ� �޸𸮰���, ���� �޸�
	//ťQueue : ���Լ���, ��������

	//Factorial : ex 8! = 8*7*6*5*4*3*2*1
	//�Ź� ¥�� �������� ������ �Լ� ���� �س���
	int oValue = Factorial(4);
	oValue = Factorial(8); //�ݺ�������
	oValue = Factorial_Re(8); //����Լ�����
	
	oValue = Fibonacci(10);
	oValue = Fibonacci_Re(10);

	//�迭 : �޸𸮰� �������� ����!
	int iArray[10] = { }; //10��¥�� �迭�� ����,{ } ������ ���� 0 ���� 
	iArray[4] = 10; //5��° �ε����� ����, 10���� ����, �迭 �ʰ��ؼ� �����ϸ� �ٸ� �����Ϳ� �̻��� ����

	//����ü
	MYST t;
	t.a = 10;
	t.f = 10.2312f;

	int iSize = sizeof(MYST);

	return 0;


}
