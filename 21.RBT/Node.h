#pragma once

//노드의 색상을 나타내는 열겨형
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
	//데이타 필드.
	int data = 0;

	//부모 노드.
	Node* parent = nullptr;
	
	//왼쪽 자손 노드.
	Node* left = nullptr;
	//오른쪽 자손 노드.
	Node* right = nullptr;

	//색상
	Color color = Color::Red;
};