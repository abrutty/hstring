#include <iostream>

class hstring
{
public:
	hstring(char* s);
	~hstring();
	char* enlarge(); // 扩容
	int find(const char* s); // 查找子串，不存在返回-1,存在多个返回第一个
	void update(const char* sub, const char* replace);// 用新字符串replace替换子串sub
	hstring& operator+(const char* s); // 重载+ 实现增加字符串
	hstring& operator-(const char* s); //重载- 实现删除子串
	hstring& operator=(int m); //重载= 实现整数转换为字符串

	//重载= 使得能够赋值
	hstring& operator=(hstring& hs){return *this;}
	
	void print()
	{
		std::cout << hstr << std::endl;
		std::cout << "容量:" << capcity << " 长度:" << length << std::endl;
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
	int pos = -1;  // 子串位置
	for (int i = 0; hstr[i] != 0; ++i)
	{
		if (hstr[i] == s[0])
		{
			int j = i;
			int idx = 0;
			while (s[idx] != 0) //看子串每个字符是否匹配
			{
				if (hstr[j] != s[idx])
				{
					break;
				}
				idx++;
				j++;
			}
			if (s[idx] == 0)  //子串匹配
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
		std::cout << "子串不存在" << std::endl;
		return;
	}
	int slen = 0, rlen = 0;
	int hlen = length;
	for (; sub[slen] != 0; slen++) {}
	for (; replace[rlen] != 0; rlen++) {}
	length = length + rlen - slen;

	if (length >= capcity)  // 需要扩容
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
	else // 不需要扩容
	{
		if (slen > rlen) // 替换的串短，向前占位
		{
			int blank = slen - rlen;
			int start = pos + slen;  //从start开始，向前移动
			for (int i = start; i <= hlen; ++i){ hstr[i - blank] = hstr[i];}
		}
		if (slen < rlen) // 替换的串长，向后空位
		{
			int blank = rlen - slen;
			//从最后一位向后移动，空出位置
			for (int i = hlen; i >= pos + slen; i--) {hstr[i + blank] = hstr[i];}
		}

		for (int i = 0, idx=pos; replace[i] != 0; ++i,++idx){hstr[idx] = replace[i];}
	}
}

hstring& hstring::operator+(const char* s) // 重载+ 实现增加字符串
{
	int slen = 0;
	int hlen = length;
	for (; s[slen] != 0; slen++) {}
	length = hlen + slen;  //新串长度
	if (length >= capcity)  //需要扩容
	{
		char* ptr = enlarge();  //临时存放添加后的字符串
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
	else  //不需要扩容
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
	int pos = find(s);  //子串的起始位置
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
	char temp[20];  // 临时保存每位数
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
	
	if (length >= capcity){ ptr = enlarge(); } //需要扩容
	else  { ptr = hstr;} // 不需要扩容

	if (n < 0) { ptr[0] = '-'; }
	while (i >= 0)
	{
		ptr[j++] = temp[i--];
	}
	ptr[j] = 0;

	if (ptr != hstr) // 扩容了，删除旧内存
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
	std::cout << "输入字符串" << std::endl;
	std::cin >> s;
	hstring hs(s);
	hs.print();

	std::cout << std::endl << "输入添加的字符串" << std::endl;
	char s1[20];
	std::cin >> s1;
	hs = hs + s1;
	std::cout << "增加后：" << std::endl;
	hs.print();

	std::cout << std::endl << "输入要删除的子串" << std::endl;
	char s2[20];
	std::cin >> s2;
	hs = hs - s2;
	std::cout << "删减后：" << std::endl;
	hs.print();

	std::cout << std::endl << "输入要查找的子串" << std::endl;
	char s3[20];
	std::cin >> s3;
	int pos = hs.find(s3);
	if (pos == -1){ std::cout << "没有该子串" << std::endl;}
	else{ std::cout << "起始位置：" << pos << std::endl;}
	
	// 用abc替换子串
	hs.update(s3, "abc");
	std::cout << std::endl << "用abc替换查找的子串" << std::endl;
	hs.print();

	std::cout << std::endl << "输入要转换的整数" << std::endl;
	int n = 0;
	std::cin >> n;
	hs = n;
	std::cout << "转换后的字符串：" << std::endl;
	hs.print();
	return 0;
}