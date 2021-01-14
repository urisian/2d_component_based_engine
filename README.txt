ObjectManager에 Add하는건 base class에서.

Initialize는 finalClass의 constructor에서 부른다.
부모클래스의 Initialize는 __super::Initialize()로 호출한다.

Component Initialize는 AddComponent안에서 자동으로 한다.
Component Update는 각각의 매니저에서 한다.


Data file의 포맷은
>기본StateKey_변수명=값<
이다


Position계산법
1.PhysicsComponent가 Position 값을 계산한다 (ParentPosition 포함)
2.PhysicsComponent가 Owner의 Position 값을 변경한다(finalPosition)
3.GraphicsComponent가 Owner에서 Position 값을 받아간다(finalPosition)



bind 공부할 것.
ClickableComponent에 Play관련 (함수포인터)



링박스는 예외적으로 따로 이니셜라이즈 함. 상속받는 대신.


ClickableComponent랑 CollisionComponent는 CollisionManager에서 업데이트 및 관리
Object는 ObjecTmanager에서
GraphicsComponent는 GraphicManager에서 관리하자. 리스트 따로 파고.



스테이지에 데코레이션 넣는 법.
Stage iniFile에 NumOfDecoration 숫자를 1추가.
decoration#_objKey=넣을데코레이션의_텍스쳐_오브젝트_키
decoration#_m_pos=넣을데코레이션의_인게임_포지션

스테이지 ini파일의 decoration0(첫데코레이션)은 배경화면이어야 한다.


Mouse의 ZOrder는 10000
UI는 9000++
Unit은 7000
Turret이 6000
Decoration은 5000