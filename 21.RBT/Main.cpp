#include <iostream>
#include "RedBlackTree.h"
#include <Windows.h>
#include <vector>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// ��� ������ ���� ������.
enum class Command
{
    None,
    Insert,
    Delete,
    Find,
    Print,
    Quit
};

// ȭ�� ����� �Լ�.
void ClearScreen()
{
    system("cls");
}

void ProcessCommandInput(int& commandInput)
{
    // �Է� ó��.
    char inputBuffer[100] = {};

    while (true)
    {
        // �Է� �ȳ� ��� �� �Է� ����.
        std::cout << "��� ���ڸ� �Է��ϼ���.\n";
        std::cout << "(1)��� �߰�, (2)��� ����, (3)��� �˻�, (4)��� ���, (5)����\n";
        std::cin >> inputBuffer;

        // atoi: ascii to integer.
        if (commandInput = atoi(inputBuffer))
        {
            // ����ó��.
            if (commandInput <= (int)Command::None
                || commandInput > (int)Command::Quit)
            {
                ClearScreen();
                std::cout << "����: �߸��� ���ڸ� �Է��߽��ϴ�.\n";
                continue;
            }

            break;
        }

        // ����ó��.
        ClearScreen();
        std::cout << "����: ����� ���ڸ� �Է��ؾ� �մϴ�.\n";
    }
}

// �Ķ���� �Է� ó�� �Լ�.
void ProcessParamInput(int& param)
{
    // �Է� ó�� ����.
    char inputBuffer[100] = { };

    // �Է� ó�� ����.
    while (true)
    {
        std::cout << "�Ķ���͸� �Է��ϼ��� (1-200).\n";
        std::cin >> inputBuffer;

        // ����.
        if (param = atoi(inputBuffer))
        {
            // ����ó��.
            if (param < 1 || param > 200)
            {
                ClearScreen();
                std::cout << "����: �Ķ���ʹ� 1-200 ������ ���ڸ� �Է��ؾ� �մϴ�.\n";
                continue;
            }

            break;
        }

        // ���� ó��.
        ClearScreen();
        std::cout << "����: �Ķ���ʹ� ���ڸ� �Է��ؾ� �մϴ�.\n";
    }
}

// ��� ó�� �Լ�.
void ProcessCommand(int commandInput, RedBlackTree& tree)
{
    // �Է� ���� ���������� ��ȯ.
    Command command = (Command)commandInput;
    if (command == Command::Print)
    {
        ClearScreen();
        tree.Print();
        return;
    }

    // ���α׷� ����.
    if (command == Command::Quit)
    {
        //exit(0);
        return;
    }

    // 1,2,3 ��� ó�� (�Ķ���� �Է��� �߰��� �ʿ���).
    int param = 0;
    ProcessParamInput(param);

    // 1/2/3 ��� ó��.
    switch (command)
    {
        // ��� �߰�.
    case Command::Insert:
    {
        ClearScreen();
        tree.Insert(param);
    } break;

    //case Command::Delete:
    //{
    //    ClearScreen();
    //    tree.Remove(param);
    //} break;

    case Command::Find:
    {
        ClearScreen();

        // �˻�.
        Node* result = nullptr;
        if (!tree.Find(param, result))
        {
            // �˻� ����.
            std::cout << "��带 ã�� ���߽��ϴ�. (�˻� ��: " << param << ")\n";
            return;
        }

        // ��� ���� ���� �ܼ� �ؽ�Ʈ ���� ����.
        if (result->GetColor() == Color::Red)
        {
            SetTextColor(TextColor::Red);
        }
        else
        {
            SetTextColor(TextColor::White);
        }

        // �˻� ��� ���.
        std::cout
            << "�˻��� ���: " << result->GetData()
            << " (Color: " << result->GetColorString()
            << ")\n";

        // �ܼ� �ؽ�Ʈ ����.
        SetTextColor(TextColor::White);

    } break;
    }
}

int main()
{
    // �޸� ���� �˻�.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // ���� �� Ʈ�� ����.
    RedBlackTree tree;

    while (true)
    {
        // ��� �Է� ó��.
        int commandInput = 0;
        ProcessCommandInput(commandInput);

        // ��� ó��.
        ProcessCommand(commandInput, tree);

        // ���� ó��.
        if (commandInput == (int)Command::Quit)
        {
            break;
        }
    }
}