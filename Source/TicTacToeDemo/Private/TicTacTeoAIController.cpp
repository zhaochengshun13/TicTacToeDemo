// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacTeoAIController.h"

#include "Checkerboard.h"

int ATicTacTeoAIController::MinimaxSearch(int Depth,int Searchdepth)
{
	InitCheckerboard
	int Value=0;
	if (Side == EBoardSide::SideA) Value = INT_MIN;
	if (Side == EBoardSide::SideB) Value = INT_MAX;
	if (Depth == Searchdepth)
	{
		Value = IsEnd();
		return Value;
	}
	int N=Checkerboard->Size;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (Board[i][j] == 0)
			{
				if (Side == EBoardSide::SideA)
				{
					Board[i][j] = 1;
					Side = EBoardSide::SideB;
					int Nextvalue = MinimaxSearch(Depth + 1);
					Side = EBoardSide::SideA;
					if (Value < Nextvalue)
					{
						Value = Nextvalue;
						if (Depth == Checkerboard->CurDepth)
						{
							BestPos.X = i;
							BestPos.Y = j;
						}
					}
				}
				else if (Side == EBoardSide::SideB)
				{
					Board[i][j] = -1;
					Side = EBoardSide::SideA;
					int Nextvalue = MinimaxSearch(Depth + 1);
					Side = EBoardSide::SideB;
					if (Value>Nextvalue)
					{
						Value = Nextvalue;
						if (Depth == Checkerboard->CurDepth)
						{
							BestPos.X = i;
							BestPos.Y = j;
						}
					}
				}
				Board[i][j] = 0;
			}
		}
	}
	return Value;
}

int ATicTacTeoAIController::Evaluate()
{
	InitCheckerboard
	int Value = IsEnd();
	if (Value == 1)return INT_MAX;
	if (Value == -1)return INT_MIN;
	int Count = 0;
	TArray<TArray<int>> Temp;
	Temp.Add(TArray<int>{0,0,0});
	Temp.Add(TArray<int>{0,0,0});
	Temp.Add(TArray<int>{0,0,0});
	int TempCount = 0;
	//用一个临时棋盘，把临时棋盘中空的部分用电脑的棋子填满，根据填满后电脑三连子的数量评估出此棋局对于电脑的价值
	for (int i = 0;i < Checkerboard->Size;i++)
	{
		for (int j = 0;j < Checkerboard->Size;j++)
		{
			if (Board[i][j] == 0)Temp[i][j] = (Side==EBoardSide::SideA?-1:1);
			else Board[i][j] = Board[i][j];
		}
	}
	//计算横向的三连子
	for (int i = 0;i <Checkerboard->Size;i++)
	{
		for (int j = 0;j <Checkerboard->Size;j++)
			TempCount += Temp[i][j];
		Count += TempCount / 3;
		TempCount = 0;
	}
	//计算纵向的三连子
	for (int i = 0;i < Checkerboard->Size;i++)
	{
		for (int j = 0;j < Checkerboard->Size;j++)
			TempCount += Temp[i][j];
		Count += TempCount / 3;
		TempCount = 0;
	}
	//计算斜向的三连子
	TempCount = (Temp[0][0] + Temp[1][1] + Temp[2][2]) / 3;
	Count += TempCount;
	TempCount = (Temp[0][2] + Temp[1][1] + Temp[2][0]) / 3;
	Count += TempCount;
	//计算此棋盘对于玩家的价值，将对于玩家的价值和对于电脑价值综合之后就是本局的价值
	for (int i = 0;i < Checkerboard->Size;i++)
	{
		for (int j = 0;j < Checkerboard->Size;j++)
		{
			if (Board[i][j] == 0)Temp[i][j] = (Side==EBoardSide::SideA?1:-1);
			else Temp[i][j] = Board[i][j];
		}
	}
	//计算横向的三连子
	for (int i = 0;i < Checkerboard->Size;i++)
	{
		for (int j = 0;j < Checkerboard->Size;j++)
			TempCount += Temp[i][j];
		Count += TempCount / 3;
		TempCount = 0;
	}
	//计算纵向的三连子
	for (int i = 0;i < Checkerboard->Size;i++)
	{
		for (int j = 0;j < Checkerboard->Size;j++)
			TempCount += Temp[i][j];
		Count += TempCount / 3;
		TempCount = 0;
	}
	//计算斜向的三连子
	TempCount = (Temp[0][0] + Temp[1][1] + Temp[2][2]) / 3;
	Count += TempCount;
	TempCount = (Temp[0][2] + Temp[1][1] + Temp[2][0]) / 3;
	Count += TempCount;

	return Count;
}

void ATicTacTeoAIController::BuildBoard()
{
	InitCheckerboard
	Board.Empty();
	Board.Add(TArray<int>{0,0,0});
	Board.Add(TArray<int>{0,0,0});
	Board.Add(TArray<int>{0,0,0});

	for (int i = 0;i < Checkerboard->Size;i++)
	{
		for (int j = 0;j < Checkerboard->Size;j++)
		{
			if(EBoardSide* Value = Checkerboard->CurrentState.Find(FVector2D(i-1,j-1)))
			{
				if((*Value)==EBoardSide::SideA)
				{
					Board[i][j]=1;
				}
				else if((*Value)==EBoardSide::SideB)
				{
					Board[i][j]=-1;
				}
				else
				{
					Board[i][j]=0;
				}
			}
			else
			{
				Board[i][j]=0;
			}
		}
	}
}

int ATicTacTeoAIController::IsEnd()
{
	InitCheckerboard
	int i, j;
	int count = 0;
	int N=Checkerboard->Size;
	for (i = 0; i < N; i++)   //行
		{
		count = 0;
		for (j = 0; j < N; j++)
			count += Board[i][j];
		if (count == 3 || count == -3)
			return count / 3;
		}
	for (j = 0; j < N; j++)   //列
		{
		count = 0;
		for (i = 0; i < N; i++)
			count += Board[i][j];
		if (count == 3 || count == -3)
			return count / 3;
		}
	count = 0;
	count = Board[0][0] + Board[1][1] + Board[2][2];
	if (count == 3 || count == -3)
		return count / 3;
	count = Board[0][2] + Board[1][1] + Board[2][0];
	if (count == 3 || count == -3)
		return count / 3;
	return 0;
}
