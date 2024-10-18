
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include "PieceStand.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Player::Player(ObjectManager* objManeger, std::string player, ModeGame* game)
{
	_objManager = objManeger;
	_game		= game;

	if (player == "player1") _kPlayerType = PLAYER_TYPE::Player1;
	if (player == "player2") _kPlayerType = PLAYER_TYPE::Player2;
}

Player::~Player()
{
}

bool Player::Initialize()
{
	_suji = _dan = 0;
	_selectedPieceIndex = -1;

	_selectSquareBoard = std::make_pair(_dan, _suji);
	_selectSquareStand = std::make_pair(_dan, _suji);

	_state = PLAYER_STATE::BoardSquare;

	_isSelectPieceOfPieceStand = false;

	return true;
}

bool Player::Terminate()
{
	return true;
}

bool Player::Process()
{
	int		player	= ConvertEnumToInt<PLAYER_TYPE>(_kPlayerType);
	auto	app		= ApplicationMain::GetInstance();
	int		trg		= 0;

#ifdef _DEBUG
	trg = app->GetTrg(player - 1);
#else
	trg = app->GetTrg(player);
#endif 

	// 将棋盤選択か駒台選択かを切り替える
	if (trg & PAD_INPUT_2)
	{
		if (_state == PLAYER_STATE::BoardSquare)
		{
			ChangeSelectBoardToStand();
		}
		else if (_state == PLAYER_STATE::PieceStandSquare)
		{
			ChangeSelectStandToBoard();
		}
	}

	// マスを選択
	SelectSquare(trg);
	
	// ターンが自分のターンでない場合、処理を行わない
	std::string strMyName			= _objManager->GetName(this);
	std::string strCurrentPlayer	= _game->GetCurrentPlayer();
	if(strCurrentPlayer != strMyName) return false;

	int index = _suji * BOARD_SIZE + _dan;
	if (trg & PAD_INPUT_4) 
	{
		// 将棋盤のマスを選択する
		if(_state == PLAYER_STATE::BoardSquare && _selectedPieceIndex == -1) SelectBoardPiece(index);
		
		else if(_state == PLAYER_STATE::DestBoardSquare) MoveBoardPiece(index);

		// 駒台のマスを選択する
		else if(_state == PLAYER_STATE::PieceStandSquare && _selectedPieceIndex == -1)
		{
			index = _suji* PIECESTAND_W + _dan;
			SelectStandPiece(index);
		}

		else if(_state == PLAYER_STATE::DestPieceStandSquare && _selectedPieceIndex != -1) MoveStandPiece(index);
	}

	return true;
}

bool Player::Render()
{
	std::unordered_map<std::string, VECTOR> box;
	std::pair<float, float>					size;
	VECTOR									pos = { 0,0,0 };

	if (_state == PLAYER_STATE::BoardSquare 
	 || _state == PLAYER_STATE::DestBoardSquare
	 || _state == PLAYER_STATE::DestPieceStandSquare)
	{
		auto board	 = dynamic_cast<Board*>(_objManager->Get("board"));
		auto square	 = board->GetSquare(_suji * BOARD_SIZE + _dan);

		size	= square->GetSize();
		pos		= square->GetPos();
	}
	else if (_state == PLAYER_STATE::PieceStandSquare)
	{
		std::string strPieceStand	= "PieceStand";
		strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";
		auto pieceStand				= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

		auto square = pieceStand->GetSquare(_suji * PIECESTAND_W + _dan);

		size	= square->GetSize();
		pos		= square->GetPos();
	}
	
	int cr		= _kPlayerType == PLAYER_TYPE::Player1 ? GetColor(255, 0, 0) : GetColor(0, 0, 255);

	box["lUp"]		= pos;
	box["lBottom"]	= VGet(pos.x, pos.y, pos.z + size.second);
	box["rUp"]		= VGet(pos.x + size.first, pos.y, pos.z);
	box["rBottom"]	= VGet(pos.x + size.first, pos.y, pos.z + size.second);

	DrawTriangle3D(box["lUp"], box["lBottom"],	box["rBottom"], cr, TRUE);
	DrawTriangle3D(box["lUp"], box["rUp"],		box["rBottom"], cr, TRUE);
	
	return true;
}

void Player::SelectSquare(int trg)
{
	if (_state == PLAYER_STATE::PieceStandSquare)
	{

		if (_suji == 2)	_dan = SelectFocus(trg, "x", PIECESTAND_W - 2, _dan);
		else			_dan = SelectFocus(trg, "x", PIECESTAND_W, _dan);

		if (_dan > 0)	_suji = SelectFocus(trg, "y", PIECESTAND_H - 1, _suji);
		else			_suji = SelectFocus(trg, "y", PIECESTAND_H, _suji);
	} 
	else if (_state == PLAYER_STATE::DestPieceStandSquare
		  || _state == PLAYER_STATE::BoardSquare
		  || _state == PLAYER_STATE::DestBoardSquare)
	{
		_dan	= SelectFocus(trg, "x", BOARD_SIZE, _dan);
		_suji	= SelectFocus(trg, "y", BOARD_SIZE, _suji);
	}
}

void Player::SelectBoardSquare(int index)
{
	if (_selectedPieceIndex == -1)
	{
		// もし選択されたマスに駒がある場合、駒を選択する
		SelectBoardPiece(index);
	}
	else
	{
		MoveBoardPiece(index);
	}
}

void Player::SelectPieceStandSquare(int index)
{
	if (_selectedPieceIndex == -1)
	{
		// もし選択されたマスに駒がある場合、駒を選択する
		SelectStandPiece(index);
	}
	else
	{
		MoveStandPiece(index);
	}
}

void Player::ChangeSelectBoardToStand()
{
	// 駒台選択に切り替える
	_state = PLAYER_STATE::PieceStandSquare;

	// 選択されたマスの情報を保存する
	_selectSquareBoard = std::make_pair(_dan, _suji);

	// 駒台選択時の選択していたマスを入れる
	_dan	= _selectSquareStand.first;
	_suji	= _selectSquareStand.second;
}

void Player::ChangeSelectDestinationBoard()
{
	// 将棋盤にある駒の移動先選択に切り替える
	_state = PLAYER_STATE::DestBoardSquare;
}

void Player::ChangeSelectStandToBoard()
{
	// 将棋盤選択に切り替える
	_state = PLAYER_STATE::BoardSquare;

	// 選択されたマスの情報を保存する
	_selectSquareStand = std::make_pair(_dan, _suji);

	// 将棋盤選択時の選択していたマスを入れる
	_dan	= _selectSquareBoard.first;
	_suji	= _selectSquareBoard.second;
}

void Player::ChangeSelectDestinationStandToBoard()
{
	// 駒台にある駒の移動先選択に切り替える
	_state = PLAYER_STATE::DestPieceStandSquare;

	// 選択されたマスの情報を保存する
	_selectSquareStand = std::make_pair(_dan, _suji);

	// 将棋盤選択時の選択していたマスを入れる
	_dan	= _selectSquareBoard.first;
	_suji	= _selectSquareBoard.second;
}

void Player::SelectBoardPiece(int index)
{
	// 駒が選択されていない場合、選択したマスに駒があるか確認
	auto ptrBoard = dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrPiece = ptrBoard->GetPiece(index);

	// 駒がない場合、処理を中断
	if (ptrPiece == nullptr) return;

	// 自分のコマでない場合、選択できない
	if (ptrPiece->GetPlayerType() != _kPlayerType) return;

	// 駒がある場合、選択したマスの情報を保存する
	auto ptrSquare		= ptrBoard->GetSquare(index);
	ptrSquare			->SetSelect(true);
	_selectedPieceIndex = index;

	ChangeSelectDestinationBoard();
}

void Player::MoveBoardPiece(int index)
{
	// 駒が選択されている場合、駒を移動
	auto board				= dynamic_cast<Board*>(_objManager->Get("board"));
	auto ptrSelectedPiece	= board->GetPiece(_selectedPieceIndex);
	auto ptrPiece			= board->GetPiece(index);

	// 相手の駒がある場合、駒を取る
	ptrPiece = TakePiece(ptrPiece);

	// コマの位置を交換する
	std::swap(ptrPiece, ptrSelectedPiece);

	// コマの位置情報を更新
	ptrPiece->SetDan(_dan);
	ptrPiece->SetSuji(_suji);

	// 駒の配列を更新
	board->SetPiece(_selectedPieceIndex, ptrSelectedPiece);
	board->SetPiece(index, ptrPiece);

	// 選択された位置に駒がある場合、駒の位置情報を更新
	if (ptrSelectedPiece	!= nullptr)	ptrSelectedPiece->SetUpdate3DPos(true);
	if (ptrPiece			!= nullptr)	ptrPiece		->SetUpdate3DPos(true);

	// 選択された位置の駒を非選択状態にする
	auto ptrSquare	= board->GetSquare(_selectedPieceIndex);
	ptrSquare		->SetSelect(false);

	// 選択した駒の情報を初期化
	_selectedPieceIndex = -1;

	_state = PLAYER_STATE::BoardSquare;

	// プレイヤーを交代する
	_game->ChangeCurrentPlayer();
}

Piece* Player::TakePiece(Piece* ptrPiece)
{
	// 指定されたインデックスの駒が存在しない場合は処理を中断
	if(!ptrPiece) return ptrPiece;

	// 自分の駒を指定された場合、処理を中断
	if(ptrPiece->GetPlayerType() == _kPlayerType) return ptrPiece;

	 // 相手のキングを取った場合、勝利処理を行う
	if (ptrPiece->GetPieceType() == PIECE_TYPE::King) 
	{
		_game->SetWin(true);
		_game->SetWinPlayer(_kPlayerType == PLAYER_TYPE::Player1 ? "player1" : "player2");
		return nullptr;
	}

	// 相手の駒を自分の持ち駒に追加
	ptrPiece->SetPlayerType(_kPlayerType);
	ptrPiece->SetOwnerType(Piece::OWNER_TYPE::PieceStand);

	// 相手の駒を自分の駒台に置く
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";
	auto pieceStand				= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));

	pieceStand->AddPiece(ptrPiece);

	return nullptr;
}

void Player::SelectStandPiece(int index)
{
	// 駒台の名前
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";

	// 駒が選択されていない場合、選択したマスに駒があるか確認
	auto						ptrStand	= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));
	PieceStand::HAS_PIECE_TYPE	type		= ConvertIntToEnum<PieceStand::HAS_PIECE_TYPE>(index);
	auto						ptrPiece	= ptrStand->GetMPiece(type);

	// 駒がない場合、処理を中断
	if (ptrPiece == nullptr) return;

	// 駒がある場合、選択したマスの情報を保存する
	auto ptrSquare	= ptrStand->GetSquare(index);
	ptrSquare		->SetSelect(true);

	_selectedPieceIndex			= index;
	_isSelectPieceOfPieceStand	= true;

	ChangeSelectDestinationStandToBoard();
}

void Player::MoveStandPiece(int index)
{
	// 駒が選択されている場合、駒を移動
	std::string strPieceStand	= "PieceStand";
	strPieceStand				+= _kPlayerType == PLAYER_TYPE::Player1 ? "1" : "2";

	auto pieceStand			= dynamic_cast<PieceStand*>(_objManager->Get(strPieceStand.c_str()));
	auto ptrBoard			= dynamic_cast<Board*>(_objManager->Get("board"));

	auto ptrSelectedPiece	= pieceStand->GetMPiece(ConvertIntToEnum<PieceStand::HAS_PIECE_TYPE>(_selectedPieceIndex));
	auto ptrPiece			= ptrBoard	->GetPiece(index);

	// 駒がある場合、処理を中断
	if(ptrPiece) return;

	// コマの位置を交換する
	ptrSelectedPiece->SetDan(_dan);
	ptrSelectedPiece->SetSuji(_suji);
	ptrSelectedPiece->SetOwnerType(Piece::OWNER_TYPE::Board);
	std::swap(ptrPiece, ptrSelectedPiece);

	// 駒の配列を更新
	pieceStand	->RemovePiece(ptrPiece);
	ptrBoard	->SetPiece(index, ptrPiece);

	// 選択された位置に駒がある場合、駒の位置情報を更新
	if (ptrPiece != nullptr) ptrPiece->SetUpdate3DPos(true);

	// 選択された位置の駒を非選択状態にする
	auto ptrSquare	= pieceStand->GetSquare(_selectedPieceIndex);
	ptrSquare		->SetSelect(false);

	// 選択した駒の情報を初期化
	_selectedPieceIndex			= -1;
	_isSelectPieceOfPieceStand	= false;

	_state = PLAYER_STATE::BoardSquare;

	// プレイヤーを交代する
	_game->ChangeCurrentPlayer();
}



