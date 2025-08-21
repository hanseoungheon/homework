#pragma once

//����� ������ ��Ÿ���� ������
enum class Color
{
	Red,
	Black,
};

class Node
{
public:
	Node(int data, Color color = Color::Red); 

	~Node() = default;

public:
	//Getter & Setter
	int GetData() const
	{
		return data;
	}

	Color GetColor() const
	{
		return color;
	}

	const char* GetColorString() const
	{

	}

	Node* GetParent() const
	{
		return parent;
	}

	Node* GetLeftChild() const
	{
		return left;
	}

	Node* GetRightChild() const
	{
		return right;
	}

	void SetData(const int newData)
	{
		data = newData;
	}

	void SetColor(const Color newColor)
	{
		color = newColor;
	}

	void SetParent(Node* newParent)
	{
		parent = newParent;
	}

	void SetLeftChild(Node* newLeft)
	{
		left = newLeft;
	}

	void SetRightChild(Node* newRight)
	{
		right = newRight;
	}

	





private:
	//����Ÿ �ʵ�.
	int data = 0;

	//�θ� ���.
	Node* parent = nullptr;
	
	//���� �ڼ� ���.
	Node* left = nullptr;
	//������ �ڼ� ���.
	Node* right = nullptr;

	//����
	Color color = Color::Red;
};