#pragma once
#include <string>
#include <vector>

namespace GL
{
//�ж��ַ��Ƿ�Ϊ���ĵĿ�ʼ�ַ�
inline bool ZH_isZHChar(char c);

//ȡ���ַ����ַ�����,������Ӣ��
size_t ZH_getStringLength(const std::string &s);

//ȡ����0Ϊ��ʼ������ָ��λ���ַ�
std::string ZH_getStringAt(std::string &s, size_t index);

//sub string
std::string ZH_subString(const std::string& s, size_t start, int count = -1);

//ȡ�ַ����е���������֧�ָ�����string���룬vector���
void GetIntegerInString(const std::string& s, std::vector<int>& vi);

//�����ַ���
int ZH_findString(const std::string& s, const std::string& sFind, size_t start=0);

//����������ת����ԭʼ����
size_t ZH_ZhIdxToOrigIdx(const std::string& s, size_t ZhIdx);

//��ԭʼ����ת������������
size_t ZH_origIdxToZhIdx(const std::string& s, size_t OrigIdx);

}

