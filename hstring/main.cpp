#include <iostream>

class hstring
{
public:
	hstring(char* s);
	~hstring();
	char* enlarge(); // ����
	int find(const char* s); // �����Ӵ��������ڷ���-1,���ڶ�����ص�һ��
	void update(const char* sub, const char* replace);// �����ַ���replace�滻�Ӵ�sub
	hstring& operator+(const char* s); // ����+ ʵ�������ַ���
	hstring& operator-(const char* s); //����- ʵ��ɾ���Ӵ�
	hstring& operator=(int m); //����= ʵ������ת��Ϊ�ַ���

	//����= ʹ���ܹ���ֵ
	hstring& operator=(hstring& hs){return *this;}
	
	void print()
	{
		std::cout << hstr << std::endl;
		std::cout << "����:" << capcity << " ����:" << length << std::endl;
	}
private:
	char *hstr;
	int length = 0;
	int capcity =0;
};

hstring::hstring(char *s)
{
	hstr = s;
	for (int i = 0; s[i] != 0; ++i)
	{
		length++;
	}
	capcity = length + 1;
	hstr = new char[capcity];
	for (int i=0 ; s[i] != 0; ++i)
	{
		hstr[i] = s[i];
	}
	hstr[length] = 0;
}

hstring::~hstring()
{
	delete[] hstr;
}

char* hstring::enlarge()
{
	while (length >= capcity)
	{
		capcity *= 2;
	}
	char* p = new char[capcity];
	return p;
}

int hstring::find(const char* s)
{
	int pos = -1;  // �Ӵ�λ��
	for (int i = 0; hstr[i] != 0; ++i)
	{
		if (hstr[i] == s[0])
		{
			int j = i;
			int idx = 0;
			while (s[idx] != 0) //���Ӵ�ÿ���ַ��Ƿ�ƥ��
			{
				if (hstr[j] != s[idx])
				{
					break;
				}
				idx++;
				j++;
			}
			if (s[idx] == 0)  //�Ӵ�ƥ��
			{
				pos = i;
				return pos;
			}
		}
	}
	return pos;
}

void hstring::update(const char* sub, const char* replace)
{
	int pos = find(sub);
	if (pos == -1)
	{
		std::cout << "�Ӵ�������" << std::endl;
		return;
	}
	int slen = 0, rlen = 0;
	int hlen = length;
	for (; sub[slen] != 0; slen++) {}
	for (; replace[rlen] != 0; rlen++) {}
	length = length + rlen - slen;

	if (length >= capcity)  // ��Ҫ����
	{
		char* ptr = enlarge();
		int idx = 0;
		for (int i = 0; hstr[i] != 0; ++i)
		{
			if (i == pos)
			{
				int ridx = 0;
				while (replace[ridx] != 0)
				{
					ptr[idx] = replace[ridx];
					idx++;
					ridx++;
				}
				if (ptr == hstr) { break; }
				i = i + slen - 1;
			}
			else
			{
				ptr[idx] = hstr[i];
				idx++;
			}
		}
		ptr[length] = 0;

		char* temp = hstr;
		hstr = ptr;
		delete[] temp;
	}
	else // ����Ҫ����
	{
		if (slen > rlen) // �滻�Ĵ��̣���ǰռλ
		{
			int blank = slen - rlen;
			int start = pos + slen;  //��start��ʼ����ǰ�ƶ�
			for (int i = start; i <= hlen; ++i){ hstr[i - blank] = hstr[i];}
		}
		if (slen < rlen) // �滻�Ĵ���������λ
		{
			int blank = rlen - slen;
			//�����һλ����ƶ����ճ�λ��
			for (int i = hlen; i >= pos + slen; i--) {hstr[i + blank] = hstr[i];}
		}

		for (int i = 0, idx=pos; replace[i] != 0; ++i,++idx){hstr[idx] = replace[i];}
	}
}

hstring& hstring::operator+(const char* s) // ����+ ʵ�������ַ���
{
	int slen = 0;
	int hlen = length;
	for (; s[slen] != 0; slen++) {}
	length = hlen + slen;  //�´�����
	if (length >= capcity)  //��Ҫ����
	{
		char* ptr = enlarge();  //��ʱ�����Ӻ���ַ���
		int idx = 0;
		for (int i = 0; hstr[i] != 0; ++i)
		{
			ptr[idx] = hstr[i];
			idx++;
		}
		for (int i = 0; s[i] != 0; ++i)
		{
			ptr[idx] = s[i];
			idx++;
		}
		ptr[length] = 0;

		char* temp = hstr;
		hstr = ptr;
		delete[] temp;
		ptr = nullptr;
	}
	else  //����Ҫ����
	{
		int idx = hlen;
		for (int i = 0; s[i] != 0; ++i)
		{
			hstr[idx] = s[i];
			idx++;
		}
		hstr[length] = 0;
	}
	return *this;
}

hstring& hstring::operator-(const char* s)
{
	int idx = 0;
	int pos = find(s);  //�Ӵ�����ʼλ��
	int i = pos;
	for (; s[idx] != 0; ++idx)
	{
		i++;
		length--;
	}

	while (hstr[i] != 0)
	{
		hstr[pos] = hstr[i];
		pos++;
		i++;
	}
	hstr[length] = 0;
	return *this;
}

hstring& hstring::operator=(int n)
{
	if (n == 0)
	{
		hstr[0] = '0';
		hstr[1] = 0;
		length = 1;
		return *this;
	}
	char temp[20];  // ��ʱ����ÿλ��
	int m = n;
	int i = 0, j = 0;
	length = 0;
	if (n < 0)
	{
		m = -m;
		j = 1;
		length++;
	}

	while (m > 0)
	{
		temp[i++] = m % 10 + '0';
		m = m / 10;
	}
	length += i;
	temp[i] = 0;
	i--;
	char* ptr = nullptr;
	
	if (length >= capcity){ ptr = enlarge(); } //��Ҫ����
	else  { ptr = hstr;} // ����Ҫ����

	if (n < 0) { ptr[0] = '-'; }
	while (i >= 0)
	{
		ptr[j++] = temp[i--];
	}
	ptr[j] = 0;

	if (ptr != hstr) // �����ˣ�ɾ�����ڴ�
	{
		char* temp = hstr;
		hstr = ptr;
		delete[] temp;
		ptr = nullptr;
	}
	return *this;
}
int main()
{
	char s[20];
	std::cout << "�����ַ���" << std::endl;
	std::cin >> s;
	hstring hs(s);
	hs.print();

	std::cout << std::endl << "������ӵ��ַ���" << std::endl;
	char s1[20];
	std::cin >> s1;
	hs = hs + s1;
	std::cout << "���Ӻ�" << std::endl;
	hs.print();

	std::cout << std::endl << "����Ҫɾ�����Ӵ�" << std::endl;
	char s2[20];
	std::cin >> s2;
	hs = hs - s2;
	std::cout << "ɾ����" << std::endl;
	hs.print();

	std::cout << std::endl << "����Ҫ���ҵ��Ӵ�" << std::endl;
	char s3[20];
	std::cin >> s3;
	int pos = hs.find(s3);
	if (pos == -1){ std::cout << "û�и��Ӵ�" << std::endl;}
	else{ std::cout << "��ʼλ�ã�" << pos << std::endl;}
	
	// ��abc�滻�Ӵ�
	hs.update(s3, "abc");
	std::cout << std::endl << "��abc�滻���ҵ��Ӵ�" << std::endl;
	hs.print();

	std::cout << std::endl << "����Ҫת��������" << std::endl;
	int n = 0;
	std::cin >> n;
	hs = n;
	std::cout << "ת������ַ�����" << std::endl;
	hs.print();
	return 0;
}