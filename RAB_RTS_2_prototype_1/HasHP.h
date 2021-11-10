#pragma once 
/*
���������� ��� ��������. �������, ���������� ��������� ������ ����������� ���� �����.
��������� �������� ���� ������� � ������ ���. ���� �������� ��������� ���� 0, ������ ������ ���� ���������
*/
class HasHP  
{
public: 
    HasHP();

    // ������� ���� �� ������� (value >= 0). ���������� ���-�� ����������� ��������
    int MakeDamage(int damage);

    // �������� ������ �� value ������� (value >= 0). ���������� ���-�� ����������� ��������
    int Heal(int value); 
     
    bool IsDead() const;

    int GetMaxHP() const;
    int GetHP() const;
    void SetMaxHP(int newValue);
    void SetHP(int newValue);

    // ������������� ������� �������� ������ �������������
    void InitHP();
private: 
    int maxHP, hp;
};

