#include"Huffman.h"

int main()
{
	int w[8] = { 5,29,7,8,14,23,3,11 };
	HuffmanTree* HT = nullptr;

	HuffmanCoding(HT, w, 8);
	display(w);

	return 0;
}