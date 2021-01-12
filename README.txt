ObjectManager에 Add하는건 base class에서.

Initialize는 finalClass의 constructor에서 부른다.
부모클래스의 Initialize는 __super::Initialize()로 호출한다.

Component Initialize는 AddComponent안에서 자동으로 한다.
Component Update는 Add해준 클래스에서 한다.


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