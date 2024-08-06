
#include "WPrintPieces.h"

#include "ObjectManager.h"
#include "ApplicationMain.h"
#include "Board.h"
#include "Shogi.h"

WPrintPieces::WPrintPieces(ObjectManager* ptrObjManager)
	: Widget(ptrObjManager)
{
}

WPrintPieces::~WPrintPieces()
{
}

bool WPrintPieces::Initialize()
{
	return true;
}

bool WPrintPieces::Terminate()
{
	return true;
}

bool WPrintPieces::Process()
{
	return true;
}

bool WPrintPieces::Render()
{
	auto				ptrBoard	= dynamic_cast<Board*>(_ptrObjManager->Get("board"));
	std::vector<Piece*> vPieces		= ptrBoard->GetPieces();

	for(int i = 0; i < vPieces.size(); ++i)
	{
		// ポインタがnullptrなら次の駒へ
		auto piece = vPieces[i];
		if (!piece) continue;

		// 駒の種類を取得
		auto type = piece->GetPieceType();
		std::string strType;
		switch (type)
		{
			case Shogi::PIECE_TYPE::Pawn:	strType = "Pawn";	break;
			case Shogi::PIECE_TYPE::Lance:	strType = "Lance";	break;
			case Shogi::PIECE_TYPE::Knight:	strType = "Knight";	break;
			case Shogi::PIECE_TYPE::Silver:	strType = "Silver";	break;
			case Shogi::PIECE_TYPE::Gold:	strType = "Gold";	break;
			case Shogi::PIECE_TYPE::Bishop:	strType = "Bishop";	break;
			case Shogi::PIECE_TYPE::Rook:	strType = "Rook";	break;
			case Shogi::PIECE_TYPE::King:	strType = "King";	break;
		}

		// ワールド座標からスクリーン座標に変換
		VECTOR pos = ConvWorldPosToScreenPos(piece->GetPos());
		pos.x -= 20; pos.y += 10;
		DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), strType.c_str());
	}

	return true;
}
