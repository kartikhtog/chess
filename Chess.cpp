// Chess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
//#include "Source.cpp"



const bool _white{ true };
const bool _black{ false };
const int _eight{ 8 };
const int _four{ 4 };
const int _five{ 5 };

enum class pieceName { nuller, Horse_1, Horse_2, Bishop_1, Bishop_2, Rook_1, Rook_2, King, Queen, Pawn_1, Pawn_2, Pawn_3, Pawn_4, Pawn_5, Pawn_6, Pawn_7, Pawn_8 };

enum class columnposition { nuller, a, b, c, d, e, f, g, h };

class PiecePoints
{
private:
	int pawn;
	int king;
	int queen;
	int horse;
	int bishop;
	int rook;

public:
	PiecePoints()
	{
		pawn = 1;
		king = 1000;
		queen = 4;
		horse = 2.2;
		bishop = 2;
		rook = 2.5;
	}
	int getPawnPoints()
	{
		return pawn;
	}
	int getKingPoints()
	{
		return king;
	}
	int getQueenPoints()
	{
		return queen;
	}
	int getHorsePoints()
	{
		return horse;
	}
	int getBishopPoints()
	{
		return bishop;
	}
	int getRookPoints()
	{
		return rook;
	}
};

class PossibleMoves
{
private:
	int king;
	int queen;
	int bishop;
	int rook;
	int horse;
	int pawn;
public:
	PossibleMoves()
	{
		king = 8;//8+28+28+28+16+4*8
		queen = 28;
		bishop = 14;
		rook = 14;
		horse = 8;
		pawn = 4;
	}
	int gking()
	{
		return king;
	}
	int gqueen()
	{
		return queen;
	}
	int gbishop()
	{
		return bishop;
	}
	int grook()
	{
		return rook;
	}
	int ghorse()
	{
		return horse;
	}
	int gpawn()
	{
		return pawn;
	}
};


class Location //column - row
{
private:
	int column_position;
	int row_position;

public:
	Location() {}

	Location(int changeColumn_position, int changeRow_position)
	{

		column_position = changeColumn_position;
		row_position = changeRow_position;
	}
	void setAll(int changeColumn_position, int changeRow_position)
	{
		column_position = changeColumn_position;
		row_position = changeRow_position;
	}
	void setRowPosition(int changeRow_Position)
	{
		row_position = changeRow_Position;
	}
	void setcolumn_position(int changeColumn_position)
	{
		column_position = changeColumn_position;
	}
	int getRowPosition()
	{
		return row_position;
	}
	int getcolumn_position()
	{
		return column_position;
	}


};

class ArrayLocation
{
private:
	int memberInArray;
	int lengthOfArray;
	Location *location;// = new Location[lengthOfArray];
public:
	ArrayLocation() {	}

	ArrayLocation(int changeLengthArray, int changeCounteri, Location *changeLocation)
	{
		lengthOfArray = changeLengthArray;
		memberInArray = changeCounteri;
		location = changeLocation;
	}

	int getSize()
	{
		return memberInArray;
	}
	int getlengthOfArray()
	{
		return lengthOfArray;
	}
	Location* getlocation()
	{
		return location;
	}

	void setSize(int changeSize)// this the current counter of array for. 0 means 1 element in array, 2 means 3 elements in array
	{
		memberInArray = changeSize;
	}
	void setLengthOfArray(int changeLength)
	{
		lengthOfArray = changeLength;
	}
	void setLocation(Location *changeLocation)
	{
		location = changeLocation;
	}
	void deletearray()
	{
		delete[] location;
		location = nullptr;
	}
};

class ChessPiece
{
private:

	std::string name;
	int rowPosition;
	columnposition column_Position = columnposition::nuller;
	bool color; // 
	pieceName piece_Name = pieceName::nuller; /// this links name to enum type such that name can be used with switch statement as string is not allow in switch statement
	bool livingStatus;// true is alive , false is dead
	int points;
public:
	ChessPiece()
	{
		livingStatus = true;
	}
	ChessPiece(std::string changeName, columnposition changeColumn_Position, int changeRowPosition, bool col, pieceName changePiece_Name,int changePoints)
	{
		column_Position = changeColumn_Position;
		rowPosition = changeRowPosition;
		name = changeName;
		color = col;
		piece_Name = changePiece_Name;
		livingStatus = true;
		points = changePoints;

	}
	void setPoints(int changePoints)
	{
		points = changePoints;
	}
	int getPoints()
	{
		return points;
	}
	void killPlayer()
	{
		livingStatus = false;
		//column_Position = columnposition::nuller;
		//rowPosition = 0;
		//piece_Name=pieceName::nuller;
		//name = "Error, you shouldn't be able to see this!, Something went wrong!!!!";
	}
	void revive()/// this is need for going back ( undo for recurstions or iterationss)
	{
		livingStatus = true;
	}
	void setColumn(columnposition changeColumn_Position)
	{
		column_Position = changeColumn_Position;
	}
	void setName(std::string changeName)
	{
		name = changeName;
	}
	void setRow(int newRowposition)
	{
		rowPosition = newRowposition;
	}
	void setColor(bool col) // white is true
	{
		color = col;
	}
	void setPieceName(pieceName changePiece_Name)
	{
		piece_Name = changePiece_Name;
	}

	int getColumn()
	{
		return static_cast<int>(column_Position);
	}
	int getRow()
	{
		return rowPosition;
	}
	std::string getName()
	{
		return name;
	}
	bool getColor()// white is true
	{
		return color;
	}
	int getPieceName()
	{
		return static_cast<int>(piece_Name);
	}
	bool getLivingStatus()
	{
		return livingStatus;
	}
};

class MovesList
{
private:
	Location  oldLocation;
	Location newLocation;
	ChessPiece * chessPiece;
	double points;
public:
	MovesList()
	{

	}
	MovesList(Location changOldLocation, Location changeNewLocation, ChessPiece * changeChessPiece)
	{
		oldLocation = changOldLocation;
		newLocation = changeNewLocation;
		chessPiece = changeChessPiece;
		points = 0;
	}
	void setAll(Location changOldLocation, Location changeNewLocation, ChessPiece * changeChessPiece)
	{
		oldLocation = changOldLocation;
		newLocation = changeNewLocation;
		chessPiece = changeChessPiece;
	}
	void setOldLocation(Location changOldLocation)//, Location* changeNewLocation, ChessPiece * changeChessPiece)
	{
		oldLocation = changOldLocation;
	}
	void setPoints(double changePoints)
	{
		points = changePoints;
	}
	double getPoints()
	{
		return points;
	}
	void setNewLocation( Location changeNewLocation)
	{
		newLocation = changeNewLocation;
	}
	void setPiece(ChessPiece * changeChessPiece)
	{
		chessPiece = changeChessPiece;
	}

	Location getOldLocation()
	{
		return oldLocation;
	}
	Location getNewLocation()
	{
		return newLocation;
	}
	ChessPiece* getPiece()
	{
		return chessPiece;
	}

		// 778 317 4119
};

void printChessBoard(ChessPiece *whitechesspieces, ChessPiece *blackchesspieces)
{
	std::string chessboard[8][8] = {};
	for (int counteri = 0; counteri < 8; counteri++)
	{
		for (int counterj = 0; counterj < 8; counterj++)
		{
			chessboard[counteri][counterj] = "0";
		}
	}
	for (int counteri = 0; counteri < 16; counteri++)
	{
		if (whitechesspieces[counteri].getLivingStatus())
		{
			chessboard[whitechesspieces[counteri].getRow() - 1][whitechesspieces[counteri].getColumn() - 1] = whitechesspieces[counteri].getName();
		}
		if (blackchesspieces[counteri].getLivingStatus())
		{
			chessboard[blackchesspieces[counteri].getRow() - 1][blackchesspieces[counteri].getColumn() - 1] = blackchesspieces[counteri].getName();
		}
	}
	std::string *alphabets = new std::string[8]{ "a","b","c","d","e","f","g","h" };

	std::cout << "   ";
	for (int counterk = 0; counterk < 8; counterk++)
	{
		std::cout << alphabets[counterk] << "  ";
	}
	delete[] alphabets;
	alphabets = nullptr;

	std::cout << "\n \n";

	for (int counteri = 0; counteri < 8; counteri++)
	{
		std::cout << counteri + 1 << "  ";
		for (int counterj = 0; counterj < 8; counterj++)
		{
			std::cout << chessboard[counteri][counterj][0] << "  "; // j is row, i is column
		}
		std::cout << "\n \n";//
	}
}

bool isrulebroken(int columnPosition, int rowPosition, int newColumn, int newRow, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ChessPiece *piece) // if rule is broken, false is return
{
	if (!(newColumn > 0 && newColumn < 9 && newRow >0 && newRow < 9)&&(*piece).getLivingStatus())
	{
		return false;
	}
	if ((*piece).getColor()) {
		for (int counterj = 0; counterj < 16; counterj++)
		{
			if ((whiteChessPieces[counterj].getRow() == newRow) && (whiteChessPieces[counterj].getColumn() == newColumn)&& whiteChessPieces[counterj].getLivingStatus())
			{
				return false;
			}
		}
	}
	if (!(*piece).getColor())
	{
		for (int counterj = 0; counterj < 16; counterj++)
		{
			if ((blackChessPieces[counterj].getRow() == newRow) && (blackChessPieces[counterj].getColumn() == newColumn) && blackChessPieces[counterj].getLivingStatus())
			{
				return false;
			}
		}
	}
	return true;
}
//if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) && )// if next piece is your team mate look for more moves in the same direction

bool isPieceOtherTeam( int newColumn, int newRow, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ChessPiece *piece) // is next player the oppsite color
/// false is returned if true
{
	if ((*piece).getColor())
	{
		for (int counterj = 0; counterj < 16; counterj++)
		{
			if ((blackChessPieces[counterj].getRow() == newRow) && (blackChessPieces[counterj].getColumn() == newColumn) && blackChessPieces[counterj].getLivingStatus())
			{
				return false;
			}
		}
	}
	if (!(*piece).getColor())
	{
		for (int counterj = 0; counterj < 16; counterj++)
		{

			if ((whiteChessPieces[counterj].getRow() == newRow) && (whiteChessPieces[counterj].getColumn() == newColumn) && whiteChessPieces[counterj].getLivingStatus())
			{
				return false;
			}
		}
	}
	return true;
}

void validMovesHorse(ChessPiece *piece, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ArrayLocation* arraylocation, int counteri)
{
	int columnPosition = (*piece).getColumn();
	int rowPosition = (*piece).getRow();
	int newColumn; // new column position
	int newRow; // new row positon
	newColumn = columnPosition + 2;
	newRow = rowPosition + 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition + 1;
	newRow = rowPosition + 2;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition - 1;
	newRow = rowPosition + 2;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition - 2;
	newRow = rowPosition + 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition - 2;
	newRow = rowPosition - 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition - 1;
	newRow = rowPosition - 2;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		

	}
	newColumn = columnPosition + 1;
	newRow = rowPosition - 2;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		

	}
	newColumn = columnPosition + 2;
	newRow = rowPosition - 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}


}

void validMovesking(ChessPiece *piece, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ArrayLocation* arraylocation, int counteri)
{
	int columnPosition = (*piece).getColumn();
	int rowPosition = (*piece).getRow();
	int newColumn; // new column position
	int newRow; // new row positon
	newColumn = columnPosition + 1;
	newRow = rowPosition + 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition + 1;
	newRow = rowPosition ;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
	counteri++;
	((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
	(*arraylocation).setSize(counteri);

	}
	newColumn = columnPosition +1;
	newRow = rowPosition -1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition ;
	newRow = rowPosition - 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition ;
	newRow = rowPosition +1 ;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}
	newColumn = columnPosition - 1;
	newRow = rowPosition - 1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		

	}
	newColumn = columnPosition -1;
	newRow = rowPosition ;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		

	}
	newColumn = columnPosition - 1;
	newRow = rowPosition +1;
	if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
	{
		counteri++;
		((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
		(*arraylocation).setSize(counteri);
		
	}


}

void validMovesBishop(ChessPiece *piece, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ArrayLocation* arraylocation,int counteri)
{
	int columnPosition = (*piece).getColumn();
	int rowPosition = (*piece).getRow();
	int newColumn; // new column position
	int newRow; // new row positon
	for (int counterj = 1; counterj < 8; counterj++) // 1
	{
		newColumn = columnPosition + counterj;
		newRow = rowPosition + counterj;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if next piece is your team mate do not look for more moves in the same direction
																																															   //&& if next piece is opposite team member
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}
	for (int counterj = 1; counterj < 8; counterj++)//2
	{
		newColumn = columnPosition - counterj;
		newRow = rowPosition + counterj;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces, piece))
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}
	for (int counterj = 1; counterj < 8; counterj++)//3
	{
		newColumn = columnPosition + counterj;
		newRow = rowPosition - counterj;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces,  piece))																																															   //&& if next piece is opposite team member
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}
	for (int counterj = 1; counterj < 8; counterj++)//4
	{
		newColumn = columnPosition - counterj;
		newRow = rowPosition - counterj;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces,  piece))
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}

}

void validMovesRook(ChessPiece *piece, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ArrayLocation* arraylocation,int counteri)
{
	int columnPosition = (*piece).getColumn();
	int rowPosition = (*piece).getRow();
	int newColumn; // new column position
	int newRow; // new row positon
	for (int counterj = 1; counterj < 8; counterj++)
	{
		newColumn = columnPosition + counterj;
		newRow = rowPosition;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if next piece is your team mate do not look for more moves in the same direction																																													   //&& if next piece is opposite team member
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);

		}
	}
	for (int counterj = 1; counterj < 8; counterj++)
	{
		newColumn = columnPosition;
		newRow = rowPosition + counterj;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if next piece is your team mate do not look for more moves in the same direction																																													   //&& if next piece is opposite team member
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}
	for (int counterj = 1; counterj < 8; counterj++)
	{
		newColumn = columnPosition - counterj;
		newRow = rowPosition;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if next piece is your team mate do not look for more moves in the same direction																																													   //&& if next piece is opposite team member
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}
	for (int counterj = 1; counterj < 8; counterj++)
	{
		newColumn = columnPosition;
		newRow = rowPosition - counterj;
		if (!isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) || isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if next piece is your team mate do not look for more moves in the same direction																																																   //&& if next piece is opposite team member
		{
			counterj = _eight;
		}
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces,piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);


		}
	}
}

void validMovesPawn(ChessPiece *piece, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ArrayLocation* arraylocation, int counteri)
{/// ad pawn cant go straight if other team piece is ahead
	int columnPosition = (*piece).getColumn();
	int rowPosition = (*piece).getRow();
	int newColumn; // new column position
	int newRow; // new row positon
	if (piece->getColor())
	{
		newRow = rowPosition - 1;
		newColumn = columnPosition;
		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece)&& isPieceOtherTeam(newColumn,newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);
		}

	}
	if (!(piece->getColor()))
	{
		newRow = rowPosition + 1;
		newColumn = columnPosition;

		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece) && isPieceOtherTeam(newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);
		}
	}
	
///////////////////
	if (piece->getColor()&& piece->getRow()==7 && isPieceOtherTeam(newColumn,_five, whiteChessPieces, blackChessPieces, piece) )
	{
		newRow = rowPosition - 2;
		newColumn = columnPosition;

		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);
		}

	}
	if ( !(piece->getColor() )  && piece->getRow()==2 && isPieceOtherTeam(newColumn, _four, whiteChessPieces, blackChessPieces, piece))
	{
		newRow = rowPosition + 2;
		newColumn = columnPosition;

		if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
		{
			counteri++;
			((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
			(*arraylocation).setSize(counteri);
		}
	}

	if (piece->getColor())
	{
		newRow = rowPosition - 1;
		newColumn = columnPosition - 1;
		for (int counterk = 0; counterk < 16; counterk++)
		{
			if (blackChessPieces[counterk].getRow() == rowPosition - 1 && blackChessPieces[counterk].getColumn()==columnPosition-1 )
			{

				if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
				{
					counteri++;
					((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
					(*arraylocation).setSize(counteri);
				}
			}
		}
	}
	if (piece->getColor())
	{
		newRow = rowPosition - 1;
		newColumn = columnPosition + 1;
		for (int counterk = 0; counterk < 16; counterk++)
		{
			if (blackChessPieces[counterk].getRow() == rowPosition - 1 && blackChessPieces[counterk].getColumn() == columnPosition + 1)
			{
				

				if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
				{
					counteri++;
					((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
					(*arraylocation).setSize(counteri);
				}
			}
		}
	}
	if (!(piece->getColor()))
	{
		newRow = rowPosition + 1;
		newColumn = columnPosition - 1;
		for (int counterk = 0; counterk < 16; counterk++)
		{
			if (whiteChessPieces[counterk].getRow() == rowPosition + 1 && whiteChessPieces[counterk].getColumn() == columnPosition - 1)
			{

				if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
				{
					counteri++;
					((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
					(*arraylocation).setSize(counteri);
				}
			}
		}
	}
	if (!(piece->getColor()))
	{
		newRow = rowPosition + 1;
		newColumn = columnPosition + 1;
		for (int counterk = 0; counterk < 16; counterk++)
		{
			if (whiteChessPieces[counterk].getRow() == rowPosition + 1 && whiteChessPieces[counterk].getColumn() == columnPosition + 1)
			{

				if (isrulebroken(columnPosition, rowPosition, newColumn, newRow, whiteChessPieces, blackChessPieces, piece))// if rule is broken, false is return)
				{
					counteri++;
					((*arraylocation).getlocation())[counteri] = { newColumn, newRow };
					(*arraylocation).setSize(counteri);
				}
			}
		}
	}
}

void validmoves(ChessPiece *piece, ChessPiece *whiteChessPieces, ChessPiece *blackChessPieces, ArrayLocation* arraylocation)
{

	
	int columnPosition = (*piece).getColumn();
	int rowPosition = (*piece).getRow();
	int newColumn; // new column position
	int newRow; // new row positon
	int counteri = (*arraylocation).getSize();
	int pieceName = ((*piece).getPieceName());


		if( pieceName==1 || pieceName == 2)
		{

			validMovesHorse(piece, whiteChessPieces, blackChessPieces, arraylocation , counteri);	

		}
		
		if (pieceName==3 || pieceName==4)// bishop
		{

			validMovesBishop(piece, whiteChessPieces, blackChessPieces, arraylocation,counteri);

		}

		if (pieceName == 5|| pieceName ==6)//rook
		{
			validMovesRook(piece, whiteChessPieces, blackChessPieces, arraylocation, counteri);
		}
		
		if (pieceName == 7)//queen
		{
			validMovesRook(piece, whiteChessPieces, blackChessPieces, arraylocation, counteri);
			validMovesBishop(piece, whiteChessPieces, blackChessPieces, arraylocation, (*arraylocation).getSize());
		}


		if (pieceName == 8)//king
		{
			validMovesking(piece, whiteChessPieces, blackChessPieces, arraylocation, counteri);
	//		std::cout << "counteri: " << (*arraylocation).getSize() << "\n";
		}


		if (pieceName >= 9 && pieceName <= 16) // pawn
		{
			validMovesPawn(piece, whiteChessPieces, blackChessPieces, arraylocation, counteri);
		}
		

}

void move(Location *newLocation, ChessPiece* piece, ChessPiece* whitechesspieces, ChessPiece* blackchesspieces)
{
	if (piece->getColor())
	{
		for (int counterk = 0; counterk < 16; counterk++)
		{
			if (blackchesspieces[counterk].getColumn() == newLocation->getcolumn_position() && blackchesspieces[counterk].getRow() == newLocation->getRowPosition())
			{
				blackchesspieces[counterk].killPlayer();
			}
		}
	}
	if (!(piece->getColor()))
	{
		for (int counterk = 0; counterk < 16; counterk++)
		{
			if (whitechesspieces[counterk].getColumn() == newLocation->getcolumn_position() && whitechesspieces[counterk].getRow() == newLocation->getRowPosition())
			{
				whitechesspieces[counterk].killPlayer();
			}
		}
	}
	piece->setColumn(static_cast<columnposition>(newLocation->getcolumn_position()));

	piece->setRow(newLocation->getRowPosition());

}

void userMove(ChessPiece *whitechesspieces,ChessPiece  *blackchesspieces)
{
	ChessPiece *thischesspiece;
	thischesspiece = &whitechesspieces[0];
	//char yolo = 'n';
	std::string stringLocation;
	int oldRow;
	int oldColumn;

		std::cout << std::endl;
		std::cout << "Enter (old column)(old row),(new column)(new row)\n";
		std::cin >> stringLocation;
		oldRow = stringLocation[1] - '0';
		oldColumn = stringLocation[0] - '0';
		int newRow = stringLocation[4] - '0';
		int newColumn = stringLocation[3] - '0';
	//	std::cout << "this is the row " << oldRow << " and this is the column " << oldColumn << "\n";
	//	std::cout << "Is the location? y/n: ";
	//	std::cin >> yolo;
		
			for (int counterk = 0; counterk < 16; counterk++)
			{
				if (whitechesspieces[counterk].getRow() == oldRow&& whitechesspieces[counterk].getColumn() == oldColumn)
				{
					thischesspiece = &whitechesspieces[counterk];
				}			
			}
			for (int counterk = 0; counterk < 16; counterk++)
			{
				if (blackchesspieces[counterk].getRow() == oldRow&& blackchesspieces[counterk].getColumn() == oldColumn)
				{
					thischesspiece = &blackchesspieces[counterk];
				}
			}

	/*		std::cout << "Is this the chesspiece " << (*thischesspiece).getName() <<" y/n : ";
			std::cin >> yolo;
		
	*/

	//std::cout << "Where do you want the chess piece to move to? \n";
	//std::cout << "Enter the location as intergers: enter row first{ eg:34 means row 3 and column 4(d) }  ";
	//std::cin >> stringLocation;

//	std::cout << "this is the row " << newRow << " and this is the column " << newColumn << "\n";


	Location newLocation{ newColumn, newRow };

	move(&newLocation, thischesspiece, whitechesspieces, blackchesspieces);
}

void makeChessBoard( ChessPiece *whitechesspieces, ChessPiece *blackchesspieces) // put string chess peices like at the begining of chess game
{

	PiecePoints piecePoints;
	whitechesspieces[0] = { "Horse 1", columnposition::b, 8,_white,pieceName::Horse_1, piecePoints.getHorsePoints() };
	whitechesspieces[1] = { "Horse 2", columnposition::g, 8 ,_white, pieceName::Horse_2 ,piecePoints.getHorsePoints()};
	whitechesspieces[2] = { "Bishop 1",columnposition::c,8 ,_white ,pieceName::Bishop_1 ,piecePoints.getBishopPoints()};
	whitechesspieces[3] = { "Bishop 2",columnposition::f,8 ,_white ,pieceName::Bishop_2 ,piecePoints.getBishopPoints()};
	whitechesspieces[4] = { "Rook 1",columnposition::a,8 ,_white ,pieceName::Rook_1 ,piecePoints.getRookPoints()};
	whitechesspieces[5] = { "Rook 2",columnposition::h,8 ,_white ,pieceName::Rook_2,piecePoints.getRookPoints() };
	whitechesspieces[6] = { "King",columnposition::e,8 ,_white ,pieceName::King, piecePoints.getKingPoints() };
	whitechesspieces[7] = { "Queen",columnposition::d,8 ,_white ,pieceName::Queen ,piecePoints.getQueenPoints() };

	for (int counteri = 8; counteri < 16; counteri++)
	{
		whitechesspieces[counteri] = { "Pawn " + std::to_string(counteri - 7),  static_cast<columnposition>(counteri - 7) ,7 ,_white,static_cast<pieceName>(counteri+1),piecePoints.getPawnPoints() };
	}

	blackchesspieces[0] = { "Horse 1", columnposition::b, 1 ,_black,pieceName::Horse_1 ,piecePoints.getHorsePoints() };
	blackchesspieces[1] = { "Horse 2", columnposition::g, 1 ,_black ,pieceName::Horse_2 ,piecePoints.getHorsePoints() };
	blackchesspieces[2] = { "Bishop 1",columnposition::c,1,_black ,pieceName::Bishop_1 ,piecePoints.getBishopPoints() };
	blackchesspieces[3] = { "Bishop 2",columnposition::f,1 ,_black ,pieceName::Bishop_2 ,piecePoints.getBishopPoints() };
	blackchesspieces[4] = { "Rook 1",columnposition::a,1 ,_black ,pieceName::Rook_1,piecePoints.getRookPoints() };
	blackchesspieces[5] = { "Rook 2",columnposition::h,1 ,_black ,pieceName::Rook_2 ,piecePoints.getRookPoints() };
	blackchesspieces[6] = { "King",columnposition::e,1 ,_black ,pieceName::King ,piecePoints.getKingPoints() };
	blackchesspieces[7] = { "Queen",columnposition::d,1 ,_black ,pieceName::Queen ,piecePoints.getQueenPoints() };
	for (int counteri = 8; counteri < 16; counteri++)
	{
		blackchesspieces[counteri] = { "Pawn " + std::to_string(counteri - 7),  static_cast<columnposition>(counteri - 7) ,2 ,_black,static_cast<pieceName>(counteri+1),piecePoints.getPawnPoints() };
	}

	std::cout << "\n";
	printChessBoard(whitechesspieces, blackchesspieces);

	/*
	std::cout << " white chess pieces!!! ***************************************************" << "\n";

	for (int counteri = 0; counteri < 16; counteri++)
	{

	Location *location = new Location[28];
	ArrayLocation arraylocation{ 28,-1,location };// -1 to show no match has occured

	validmoves(&(whitechesspieces[counteri]), whitechesspieces, blackchesspieces,&arraylocation);//, &chessboard);
	std::cout << "The number of moves for "<< whitechesspieces[counteri].getName() <<" is " << arraylocation.getSize()+1 << ". \n";
	
	for (int counterj = 0; counterj < arraylocation.getSize() +1; counterj++)// size is plus 1(to show when counter is 0, it mean on element in array )and minus one (to show when counter returns its one higher)
	{
		std::cout << " the curent position of " << whitechesspieces[counteri].getName() << " is column " << whitechesspieces[counteri].getColumn() << " and row " << whitechesspieces[counteri].getRow() << ". \n";
		std::cout << "The " << whitechesspieces[counteri].getName() << " can move to column " << location[counterj].getcolumn_position() << " and the row " << location[counterj].getRowPosition() << "\n";
	}
	arraylocation.deletearray();
	std::cout << "\n";
	}

	std::cout << " black chess pieces!!! ***************************************************" << "\n";


	for (int counteri = 0; counteri < 16; counteri++)

	{

		Location *location = new Location[28];
		ArrayLocation arraylocation{ 28,-1,location };// -1 to show no match has occured
		validmoves(&(blackchesspieces[counteri]), whitechesspieces, blackchesspieces, &arraylocation);//, &chessboard);


		std::cout << "The number of moves for " << blackchesspieces[counteri].getName() << " is " << arraylocation.getSize() +1<< ". \n";		
		for (int counterj = 0; counterj < arraylocation.getSize() + 1; counterj++)// size is plus 1(to show when counter is 0, it mean on element in array )and minus one (to show when counter returns its one higher)
		{
			std::cout << " the curent position of " << blackchesspieces[counteri].getName() << " is column " << blackchesspieces[counteri].getColumn() << " and row " << blackchesspieces[counteri].getRow() << ". \n";
			std::cout << "The " << blackchesspieces[counteri].getName() << " can move to column " << location[counterj].getcolumn_position() << " and the row " << location[counterj].getRowPosition() << "\n";
		}
		arraylocation.deletearray();
		std::cout << "\n"; //std::cout << "\n"; std::cout << "\n"; std::cout << "\n"; std::cout << "\n"; std::cout << "\n";

	}
	*/
	std::cout << "\n";

	//userMove(whitechesspieces, blackchesspieces);
		std::cout << "\n";

//	move(&newLocation, &(whitechesspieces[0]), whitechesspieces,blackchesspieces, chessboard);
	std::cout << "\n";


	
}

void loopii(bool side,int myPoints,int opponentPoints,bool turn,int deepLayers,ChessPiece* whitechesspieces, ChessPiece* blackchesspieces,std::vector<MovesList> &pathWay, bool check)//need to pass moveslist vector
//side true means white, (turn var (true means whites turn)) //  deep means how many turns including opponent
// need to program to protect king at all cost by programming no turns after king is dead
{

	/// deep should equal the number of available spaces for elements in pathWay 
	int score = myPoints - opponentPoints;
	/// need to select max of all min
	// if (chesspiece ==dead) then revive and add back points or delete points
	std::vector<MovesList> movesList;
	Location oldLocation;
	Location newLocation;
	movesList.reserve(140);
//	movesList.resize(140);
	bool kingDied = false;
	if (turn) 
	{

		int counterkkk = -1;
		for (int counteriii = 0; counteriii < 16; counteriii++)
		{
			if (whitechesspieces[counteriii].getLivingStatus())
			{
				Location *location = new Location[28];
				ArrayLocation arraylocation{ 28,-1,location };// -1 to show no match has occured
				validmoves(&(whitechesspieces[counteriii]), whitechesspieces, blackchesspieces, &arraylocation);//, &chessboard);
				if (check)
				{
					std::cout << "The number of moves for " << whitechesspieces[counteriii].getName() << " is " << arraylocation.getSize() + 1 << ". \n";
				}
				for (int counterj = 0; counterj < arraylocation.getSize() + 1; counterj++)// size is plus 1(to show when counter is 0, it mean on element in array )and minus one (to show when counter returns its one higher)
				{


					counterkkk++;
					oldLocation.setAll(whitechesspieces[counteriii].getColumn(), whitechesspieces[counteriii].getRow());
					newLocation.setAll(location[counterj].getcolumn_position(), location[counterj].getRowPosition());
					//	movesList.push_back();
					movesList.resize(counterkkk + 1);
					movesList[counterkkk].setAll(oldLocation, newLocation, &whitechesspieces[counteriii]);//
				}
				arraylocation.deletearray();

			}
			
		}
	
	}

	if (!turn)
	{
		int counterkkk = -1;

		for (int counteriii = 0; counteriii < 16; counteriii++)
		{
			if (blackchesspieces[counteriii].getLivingStatus())
			{
				Location *location = new Location[28];
				ArrayLocation arraylocation{ 28,-1,location };// -1 to show no match has occured
				validmoves(&(blackchesspieces[counteriii]), whitechesspieces, blackchesspieces, &arraylocation);//, &chessboard);

				for (int counterj = 0; counterj < arraylocation.getSize() + 1; counterj++)// size is plus 1(to show when counter is 0, it mean on element in array )and minus one (to show when counter returns its one higher)
				{
					counterkkk++;
					oldLocation.setAll( blackchesspieces[counteriii].getColumn(), blackchesspieces[counteriii].getRow() );
					newLocation.setAll( location[counterj].getcolumn_position(),location[counterj].getRowPosition() );
					//movesList.push_back();
					movesList.resize(counterkkk + 1);
					movesList[counterkkk].setAll(oldLocation, newLocation, &blackchesspieces[counteriii]);//
					
				}
				arraylocation.deletearray();

			}

		}

	}

	int counterStop;
	double maxScore=-10000000;
	double minScore=10000000;
	bool playerExistsNewLocation = false;
	// if king is killed then stop going into deeperlayers without changing the deeplayers variable

	if (side == turn)
	{
		for (int counteriii = 0; counteriii < movesList.size(); counteriii++)
		{
			playerExistsNewLocation = false;
			if (!turn)
			{
				for (int counterk = 0; counterk < 16; counterk++)
				{
					if (whitechesspieces[counterk].getLivingStatus() && whitechesspieces[counterk].getColumn() == movesList[counteriii].getNewLocation().getcolumn_position() && whitechesspieces[counterk].getRow() == movesList[counteriii].getNewLocation().getRowPosition())
					{
						whitechesspieces[counterk].killPlayer();
						if (whitechesspieces[counterk].getName()=="King")
						{
							kingDied = true;
						}

						playerExistsNewLocation = true;
						counterStop = counterk;
						opponentPoints = opponentPoints - whitechesspieces[counterk].getPoints();

					}
				}
			}
			if (turn)
			{
				for (int counterk = 0; counterk < 16; counterk++)
				{
					if (blackchesspieces[counterk].getLivingStatus()&&blackchesspieces[counterk].getColumn() == movesList[counteriii].getNewLocation().getcolumn_position() && blackchesspieces[counterk].getRow() == movesList[counteriii].getNewLocation().getRowPosition())
					{


							blackchesspieces[counterk].killPlayer();
							if (blackchesspieces[counterk].getName() == "King")
							{
								kingDied = true;
							}
							playerExistsNewLocation = true;
							counterStop = counterk;
							opponentPoints = opponentPoints - blackchesspieces[counterk].getPoints();
						
							
					}

				}
			}
			
			movesList[counteriii].getPiece()->setColumn(static_cast<columnposition>(movesList[counteriii].getNewLocation().getcolumn_position())); //the problem is here
			movesList[counteriii].getPiece()->setRow(movesList[counteriii].getNewLocation().getRowPosition()); // the problem is here
			score = myPoints - opponentPoints;


			if (score >= maxScore && deepLayers==0 || kingDied)
			{
				maxScore = score;
				oldLocation.setAll( movesList[counteriii].getOldLocation().getcolumn_position(), movesList[counteriii].getOldLocation().getRowPosition()) ;
				newLocation.setAll( movesList[counteriii].getNewLocation().getcolumn_position(), movesList[counteriii].getNewLocation().getRowPosition() );

				pathWay[deepLayers].setAll(oldLocation, newLocation, (movesList[counteriii].getPiece()));//need to store infomation about this move

				pathWay[deepLayers].setPoints(maxScore);
			
			}

			if( deepLayers>0 && !kingDied)
			{
				
					loopii(side, myPoints, opponentPoints, !turn, deepLayers - 1, whitechesspieces, blackchesspieces, pathWay, false);
				
				

				
				if (pathWay[deepLayers - 1].getPoints() >= maxScore)
				{
					
					oldLocation.setAll(movesList[counteriii].getOldLocation().getcolumn_position(), movesList[counteriii].getOldLocation().getRowPosition());
					newLocation.setAll(movesList[counteriii].getNewLocation().getcolumn_position(), movesList[counteriii].getNewLocation().getRowPosition());
					maxScore = pathWay[deepLayers - 1].getPoints();
					pathWay[deepLayers] = { oldLocation,newLocation,movesList[counteriii].getPiece() };
					pathWay[deepLayers].setPoints(maxScore);

					

				}

			}

			//score = myPoints - opponentPoints;//max score
			movesList[counteriii].getPiece()->setColumn(static_cast<columnposition>(movesList[counteriii].getOldLocation().getcolumn_position()));
			movesList[counteriii].getPiece()->setRow(movesList[counteriii].getOldLocation().getRowPosition());

			if ((!turn) && playerExistsNewLocation)
			{
				opponentPoints = opponentPoints + whitechesspieces[counterStop].getPoints();
				whitechesspieces[counterStop].revive();
			}
			if ((turn) && playerExistsNewLocation)
			{
				opponentPoints = opponentPoints + blackchesspieces[counterStop].getPoints();
				blackchesspieces[counterStop].revive();
			}


		}
		

	}
	

	if (!(side == turn))
	{
		for (int counteriii = 0; counteriii < movesList.size(); counteriii++)
			{
				bool playerExistsNewLocation = false;
				if (!turn)
				{
					for (int counterk = 0; counterk < 16; counterk++)
					{
						if (whitechesspieces[counterk].getLivingStatus() && whitechesspieces[counterk].getColumn() == movesList[counteriii].getNewLocation().getcolumn_position() && whitechesspieces[counterk].getRow() == movesList[counteriii].getNewLocation().getRowPosition())
						{
							whitechesspieces[counterk].killPlayer();
							if (whitechesspieces[counterk].getName() == "King")
							{
								kingDied = true;
							}
							playerExistsNewLocation = true;
							counterStop = counterk;
							myPoints = myPoints - whitechesspieces[counterk].getPoints();
						}
					}
				}
				if (turn)
				{
					for (int counterk = 0; counterk < 16; counterk++)
					{
						if (blackchesspieces[counterk].getLivingStatus() && blackchesspieces[counterk].getColumn() == movesList[counteriii].getNewLocation().getcolumn_position() && blackchesspieces[counterk].getRow() == movesList[counteriii].getNewLocation().getRowPosition())
						{
							blackchesspieces[counterk].killPlayer();
							if (blackchesspieces[counterk].getName() == "King")
							{
								kingDied = true;
							}
							playerExistsNewLocation = true;
							counterStop = counterk;
							myPoints = myPoints - blackchesspieces[counterk].getPoints();

						}
					}
				}

				movesList[counteriii].getPiece()->setColumn(static_cast<columnposition>(movesList[counteriii].getNewLocation().getcolumn_position()));
				movesList[counteriii].getPiece()->setRow(movesList[counteriii].getNewLocation().getRowPosition());
				score = myPoints - opponentPoints;
				if (score <= minScore&&deepLayers==0 || kingDied)//change to min score
				{
					minScore = score;// score = myPoints - opponentPoints;

					oldLocation.setAll(movesList[counteriii].getOldLocation().getcolumn_position(), movesList[counteriii].getOldLocation().getRowPosition());
					newLocation.setAll(movesList[counteriii].getNewLocation().getcolumn_position(), movesList[counteriii].getNewLocation().getRowPosition());
					pathWay[deepLayers].setAll( oldLocation,newLocation,movesList[counteriii].getPiece() );//need to store infomation about this move
					pathWay[deepLayers].setPoints(minScore);

					



				}
				if (deepLayers>0 && !kingDied)
				{
					loopii(side, myPoints, opponentPoints, !turn, deepLayers - 1, whitechesspieces, blackchesspieces, pathWay,false);
	
					if (pathWay[deepLayers - 1].getPoints() <= minScore)
					{
						oldLocation.setAll(movesList[counteriii].getOldLocation().getcolumn_position(), movesList[counteriii].getOldLocation().getRowPosition());
						newLocation.setAll(movesList[counteriii].getNewLocation().getcolumn_position(), movesList[counteriii].getNewLocation().getRowPosition());
						minScore = pathWay[deepLayers - 1].getPoints();
						pathWay[deepLayers] = { oldLocation,newLocation,movesList[counteriii].getPiece() };
						pathWay[deepLayers].setPoints(minScore);

						
	
					}

				}
				movesList[counteriii].getPiece()->setColumn(static_cast<columnposition>(movesList[counteriii].getOldLocation().getcolumn_position()));
				movesList[counteriii].getPiece()->setRow(movesList[counteriii].getOldLocation().getRowPosition());
				if ((!turn) && playerExistsNewLocation)
				{
					myPoints = myPoints + whitechesspieces[counterStop].getPoints();
					whitechesspieces[counterStop].revive();
				}
				if ((turn) && playerExistsNewLocation)
				{
					myPoints = myPoints + blackchesspieces[counterStop].getPoints();
					blackchesspieces[counterStop].revive();
				}

			}

	}

}

//// advance - other person will make the move given most points in next few moves
/// advance - program will learn the type of player
//// move for each chess peice
//// create a scinaro for each chess piece //move chess peice then change turn

int main()
{

	ChessPiece *blackchesspieces = new ChessPiece[16];
	ChessPiece* whitechesspieces = new ChessPiece[16];

	makeChessBoard(whitechesspieces, blackchesspieces);

	printChessBoard(whitechesspieces, blackchesspieces);

	PiecePoints piecePoints;
	int teamPoints = 0;
	teamPoints = teamPoints + piecePoints.getBishopPoints() * 2;
	teamPoints = teamPoints + piecePoints.getHorsePoints() * 2;
	teamPoints = teamPoints + piecePoints.getRookPoints() * 2;
	teamPoints = teamPoints + piecePoints.getKingPoints();
	teamPoints = teamPoints + piecePoints.getPawnPoints() * 8;
	teamPoints = teamPoints + piecePoints.getQueenPoints();
	std::cout << "\n The total team points are " << teamPoints << ".\n";
	bool check = false;
	bool turn = true;
	bool side = turn;

	std::string play = "y";
	std::string User_computer_play = "y";
	std::cout << "Type y for computer vs User / Type n for computer vs computer: ";
	std::cin >> User_computer_play;
	while (User_computer_play == "y")
	{

		std::vector<MovesList> pathWay;
		int temp = 4;
		pathWay.reserve(temp);
		pathWay.resize(temp);
		/// need to sum current team points before moving 
		loopii(turn, teamPoints, teamPoints, side, temp - 1, whitechesspieces, blackchesspieces, pathWay, false);

		move(&pathWay[temp - 1].getNewLocation(), pathWay[temp - 1].getPiece(), whitechesspieces, blackchesspieces);
		printChessBoard(whitechesspieces, blackchesspieces);
		std::cout << "\n";
		userMove(whitechesspieces, blackchesspieces);
		printChessBoard(whitechesspieces, blackchesspieces);
		std::cout << "\n";




	}

	
	
	while (play == "y" && User_computer_play=="n")
	{
	
	std::vector<MovesList> pathWay;
	int temp = 4;
	pathWay.reserve(temp);
	pathWay.resize(temp);

	loopii(turn, teamPoints, teamPoints, side, temp - 1, whitechesspieces, blackchesspieces, pathWay, false);

	turn = !turn;
	side = turn;
	// something wrong with the score system

	for (int counterggg=temp - 1; counterggg >= 0;counterggg--)
	{

		std::cout << "the color of the piece is " << (*(pathWay[counterggg].getPiece())).getColor() << " \n";
		std::cout << "the color of the piece is " << (*(pathWay[counterggg].getPiece())).getName() << " \n";
		std::cout << "The old column position is [ " << pathWay[counterggg].getOldLocation().getcolumn_position();
		std::cout << " ] and old row position is [ " << pathWay[counterggg].getOldLocation().getRowPosition() << " ] \n";
		std::cout << "The column position is [ " << pathWay[counterggg].getNewLocation().getcolumn_position();
		std::cout << " ] and row position is [" << pathWay[counterggg].getNewLocation().getRowPosition() << " ] \n";
		std::cout << "Points: " << pathWay[counterggg].getPoints() << "\n \n";
	}
	std::cout << "Do you want to make this move? y/n \n";
	std::string makemove = "y";
	std::cin >> makemove;

	if (makemove == "y")
	{
		move(&pathWay[temp - 1].getNewLocation(), pathWay[temp - 1].getPiece(), whitechesspieces, blackchesspieces);
		printChessBoard(whitechesspieces, blackchesspieces);

	}
	


	std::cout << "Do you want to play more? y/n ";
	std::cin >> play;


	}


	printChessBoard(whitechesspieces, blackchesspieces);
	delete[] whitechesspieces;
	whitechesspieces = nullptr;
	delete[] blackchesspieces;
	blackchesspieces = nullptr;

	return 0;

}

/// references do implicit dereferences
