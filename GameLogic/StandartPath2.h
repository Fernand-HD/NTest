#pragma once

#include "Path.h"
#include "PFWorldObjectBase.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonStaticPath;

namespace Pathfinding
{
  class CCommonPathFinder;
}

namespace NWorld
{

_interface IPointChecking;
class PFBaseMovingUnit;


// TODO: remove IPath, remove "virtual" from functions

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStandartPath2 : public IPath, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS(0x3121AC40, CStandartPath2);

	CPtr<TileMap> pMap;
	CPtr<Pathfinding::CCommonPathFinder> pathFinder;

	ZDATA_(PFWorldObjectBase)
  ZNOPARENT(IPath)
	ZNOCRC

	int     nBoundTileRadius;
	int     nBoundTileRadiusDyn;

	CPtr<CCommonStaticPath> pStaticPath;
	int     nCurStaticPathTile;	// ������������ � CalculatePath() � RecoverPath()

	CVec2   vStartPoint;				// ��������� ����� �������� ����� (����� ���� ������� ������������ pStaticPath ��� ������)
	CVec2   vFinishPoint;				// �������� ����� �������� �����
	SVector vFinishTile;				// �������� ����� �������� ����� ��� ����

	int     remainingLength;		// ����� ������� ���� � ������

	vector<SVector> insTiles;
	int     nCurInsTile;

	vector<SVector> pathTiles;
	int     nCurPathTile;				// �������������� ������ �� Shift()
	int     nLastPathTile;			// �������������� ������ �� CopyPath(); ��������� �� ��������� ����������� ���� ������������ ����
	CPtr<IPointChecking> pointChecking;


	int              timestamp;
	ZNOCRCEND
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this);  if(!f.IsChecksum()){ f.Add(2,&nBoundTileRadius); f.Add(3,&nBoundTileRadiusDyn); f.Add(4,&pStaticPath); f.Add(5,&nCurStaticPathTile); f.Add(6,&vStartPoint); f.Add(7,&vFinishPoint); f.Add(8,&vFinishTile); f.Add(9,&remainingLength); f.Add(10,&insTiles); f.Add(11,&nCurInsTile); f.Add(12,&pathTiles); f.Add(13,&nCurPathTile); f.Add(14,&nLastPathTile); f.Add(15,&pointChecking); f.Add(16,&timestamp);  } return 0; }
private:

	void CopyPath( const int nLength );
	void Smooth();
	const bool CalculatePath( const bool bShift, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps );
  const bool CalculateShortPath( const SVector &vDest, const bool bShift, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps );

	void SetFinishTile( const SVector &_vFinishTile );

	void InitByStaticPath( CCommonStaticPath *pStaticPath, const CVec2 &vStartPoint, const CVec2 &vFinishPoint, int numSteps );

  CStandartPath2();

public:
  // construct CStandartPath2 from static path
	CStandartPath2( Pathfinding::CCommonPathFinder* _pathFinder, int objectTileSize, int objectDynTileSize, CCommonStaticPath *pStaticPath, IPointChecking *pChecking, const CVec2 &vStartPoint, const CVec2 &vFinishPoint, TileMap *pMap, int numSteps );

	virtual void Reset();

	virtual bool CanPeek( int nShift ) const;
	virtual const CVec2 PeekPoint( const int nShift ) const;
	virtual void Shift( const int nShift, int numSteps );
	virtual bool IsFinished() const { return nCurPathTile == nLastPathTile; }

	virtual const CVec2& GetFinishPoint() const { return vFinishPoint; }
	virtual const CVec2& GetStartPoint() const { return vStartPoint; }

	bool TryUpdatePath(const CVec2 &target);
	// ������������ (����������� ����� ����������� ����) ���� �� ����� ����� ( vPoint )
	virtual void RecoverPath( const CVec2 &vPoint, const SVector &vLastKnownGoodTile, int numSteps );
	// ����������� ���� �� ����� ����� ( vPoint ); ������ false, ���� ���� �� ��������
	virtual bool RecalcPath( const CVec2 &vPoint, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps );
  virtual bool CalcShortPath( const SVector &vDest, const CVec2 &vPoint, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps );
	// �������� ����� � ������ ����, ��� ����������� ����������� ����� InsertTiles ���������� ������� RecoverPath
	virtual void InsertTiles( const list<SVector> &tiles );
  // ���������� ��������� ����� �� ������������ ��� ����, ��� �� ����� �� ������� ����
	virtual const bool ShouldCheckTurn() const { return true; }
	// ����� �� ��� ����� ���� ��������� ������� �������� (��� ����� ���������� �� ���������� ���� ���)
	virtual const bool CanBuildComplexTurn() const { return false; }
	virtual bool NeedToBeStepped() { return false; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
