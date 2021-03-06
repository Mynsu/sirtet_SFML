﻿Sirtet
======
예, 맞습니다.  [테트리스](https://tetris.fandom.com/wiki/Tetris_Guideline) 데모입니다.   
   
<a href="https://youtu.be/21LZqKT6xyA" target="_blank"><img src="https://user-images.githubusercontent.com/43042411/78128235-8cffc700-7450-11ea-990a-ffefc8c9c2bf.jpg" width="600" height="337" border="0"></a> *( 유투브 링크 )*


테트리스를 만든 이유는
----------------------
+ 3D 그래픽스 수학 연산, 물리 연산이 없어 심사원께서 **코드 기본**만 살피시기에 편하고,
+ 게임과 코드 모두 심사원께 익숙하기까지 하다면 심사하는 데 **피로가 덜할** 것이며,
+ [여기](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/your-first-step-to-game-development-starts-here-r2976/)[저기](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/how-do-i-make-games-a-path-to-game-development-r892/)에서 추천한 게임들 중 **게임 플레이 로직**이 제 머릿속에 그려지지 않은 유일한 게임이었고,
+ **하고 싶지 않은 게임이더라도** 끝까지 만들어 낼 수 있을지 제 자신이 궁금했기 때문입니다.

 
언어와 개발 환경은
------------------
C++ 17, Lua 5.3, 비주얼 스튜디오 2017(15.9) 그리고 윈도우즈 10(1803) x64입니다.


빌드와 실행에 필요한 외부 라이브러리와 운영체제는
----------------------------------------------
**NuGet**으로 관리하면 이슈가 있어 아래의 방법을 추천합니다.
+ \[클라이언트] Lua 5.3.0 이상
> 설치 예)
> 1. [다운로드 페이지](https://sourceforge.net/projects/luabinaries/files/5.3.5/Windows%20Libraries/Dynamic/)에서 *lua-5.3.5_Win64_dll15_lib.zip* 다운로드
> 2. *./externals/Lua-5.3/x64/* 에 *include* 폴더 압축 풀기
>   *./externals/Lua-5.3/x64/lib/* 에 *lua53.lib* 압축 풀기
> 3. *빌드된 Sirtet.exe와 Game.dll이 있는 디렉토리* 에 *lua53.dll* 압축 풀기
+ \[클라이언트/메인 서버] SFML 2.5.0 이상
> 설치 예)
> 1. [다운로드 페이지](https://www.sfml-dev.org/download/sfml/2.5.1/)에서 *Visual C++ 15 (2017) - 64-bit* 다운로드
> 2. *./externals/SFML-2.5/x64/* 에 *include* 폴더, *lib* 폴더 압축 풀기
> 3. *빌드된 Sirtet.exe와 Game.dll이 있는 디렉토리* 에 *openal32.dll, sfml-audio-2.dll, sfml-graphics-2.dll, sfml-system-2.dll, sfml-window-2.dll* 압축 풀기   
> *빌드된 Server.exe가 있는 디렉토리* 에 *sfml-graphics-2.dll, sfml-system-2.dll, sfml-window-2.dll* 압축 풀기   
> ( 디버그 모드로 빌드하시려면 *sfml-audio-**d**-2.dll*처럼 알파벳 **d**가 붙은 .dll 파일로 대체하십시오. )   
> ( 메인 서버에서 SFML을 쓰지 않을 예정입니다. )
+ \[클라이언트/대기열 서버/메인 서버] 윈도우즈 7 이상입니다.


빌드하시기 전에!
----------------
**서버들의 IP 주소**가 localhost로 설정되어 있습니다.  *staticLibs/GameLib/Common.h*에서 수정하실 수 있습니다.


IDE에서는 실행되는데 출력 디렉토리에서는 실행이 안 된다면
---------------------------------------------------------
**리소스 파일들이** 출력 디렉토리에 있는지 확인해주십시오.   
*./MakeSymbolicLinks.bat* 파일을 출력 디렉토리, 즉 *빌드된 Sirtet.exe와 Game.dll이 있는 디렉토리* 로 옮겨 실행하시면 편하게 리소스 파일들을 옮기실 수 있습니다.


실행하신 후에
-------------
+ BGM이 시끄러우시다면, **Ctrl + M**을 눌러주십시오.   
+ 콘솔을 켜시려면, **Tab 키**를 눌러주십시오.   
+ 씬 이동엔, **마우스와 Esc 키**를 써주십시오.   
+ **방향키와 스페이스 바**로 테트리미노를 움직이실 수 있습니다.


라이센스는 다음과 같습니다.
--------
+ [MIT](https://www.lua.org/license.html) (Lua)
+ [zlib/png](https://www.sfml-dev.org/license.php) (SFML)
+ [OFL](https://scripts.sil.org/OFL) (글꼴)


제 코드에 대해 궁금하실 만한 것들을 추렸습니다.
------------------------------------------------
**#깃 브랜칭 모형** **#깃 플로**   
  깃 플로로 버전 관리했습니다.  feature 브랜치는 develop 브랜치에 squash 병합*merge*했습니다.   
도중에 깃 플로로 갈아타면서 master 브랜치에 어울리지 않는 커밋들이 남았습니다.

**#파일 디렉토리, 필터, 이름공간 일치**   
  예로, 헤더 파일 *dlls/Game/scene/inPlay/InPlay.h*는 프로젝트 Game의 필터 scene/inPlay 아래에 있습니다.  클래스 InPlay의 이름공간도 ::scene::inPlay입니다.

**#단순한 코드 패턴** **#최소 작용의 원리(?)**   
  기능이 같은 한, 패턴이 단순하도록 코딩합니다.  패턴이 난잡한 코드는 읽고 싶지 않은데다 오류*error*까지 잦기 때문입니다.

**#헤더 파일을 포함*include*하는 순서** **#간접 포함에 기대지 않음**   
  의존하는 대로 C 표준*standard* 라이브러리, C++ 표준 라이브러리, 제 3자*3rd party* 라이브러리, 직접 만든 라이브러리, 나머지 순으로 포함합니다.   
  예외로, *WIN32_LEAN_AND_MEAN*을 정의한 다음 포함하면 컴파일 오류가 발생하는 헤더 파일은 가장 먼저 포함했습니다.   
  또, 필요한 헤더 파일이 다른 헤더 파일을 통해 간접 포함되더라도 이에 기대지 않고 직접 포함합니다.  간접 포함하면 헤더 파일을 뺄 때마다 필요한 헤더 파일까지 송두리채 빼진 않았는지 살펴야 하기 때문입니다.  또, 컴파일러가 바뀌면 헤더를 여전히 간접 포함하는 지 알 수 없기 때문입니다.   
( [각 프로젝트의 *pch.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/exes/Engine/pch.h) 등 )

**#전방 선언*forward declaration*** **#C++ 20 모듈은 아직**   
  가능한 한 소스 파일에만 헤더 파일을 포함합니다.  수정한 A.hpp를 B.hpp가 포함한다면, B.hpp를 포함하나 A.hpp는 쓰지 않는 소스 파일까지 괜히 다시 빌드하기 때문입니다.  Pimple 패턴은 쓰지 않았습니다.   
  헤더 파일에 선언된 포인터와 레퍼런스를 타입 체크해야 하더라도, 타입을 전방 선언하여 순환 참조를 예방합니다.   
( [*dlls/Game/ui/NextTetriminoPanel.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/ui/NextTetriminoPanel.h)와 [*PlayView.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/ui/PlayView.h), [*dlls/Game/scene/online/*](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game/scene/online) 아래 헤더 파일들, [*exes/Server/Room.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/exes/Server/Room.h) )

**#상수를 모아둔 헤더 파일**   
  공유하는 상수를 모아둔 헤더 파일은 있습니다만, 공유하지 않는 상수는 각 소스 파일에 있습니다.  이유는 **#전방 선언**에서 헤더 파일을 되도록 소스 파일에만 포함하는 이유와 같습니다.   
( [*staticLibs/GameLib/Common.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/staticLibs/GameLib/Common.h) )

**#인터페이스** **#접두사 I** **#protected** **#남용하지 않음**   
  순수 가상 함수만 선언된 기반*base*·직계존속(?)*parent*·상위·추상 클래스라는 이명들 대신 자바의 인터페이스라는 이름을 차용하겠습니다.  이 저장소에서 다른 의미의 '인터페이스'는 쓰지 않습니다.   
  인터페이스 이름 앞에 알파벳 대문자 I를 붙입니다.  이것만으로도 인스턴스를 함부로 만들지 않도록 유도할 수 있습니다.  또, 코드의 중의성이 사라져 문법*syntax*상 상속이지만 실은 구현*implement*임을 쉽게 파악할 수 있습니다.   
  인터페이스 생성자의 접근 한정자를 protected로 둔 것도 인스턴스를 함부로 만들지 않도록 하기 위한 것입니다.   
  런타임 다형성은 남용하지 않도록 주의합니다.  힙에 간접 접근하고 병합으로 성능을 손해보기 때문입니다.   
( [*dlls/Game/scene/*](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game/scene) 아래 *IScene.h*들 )

**#상속** **#컴포지트*composite***   
  인터페이스 구현에만 문법상 상속을 썼습니다.   
  다음과 같은 이유로 상속을 지양합니다.
1. 하위 클래스와 상위 클래스가 'is-a' 관계라도 둘의 경계에서 갈팡질팡하는 속성, 즉 변수가 있기 마련입니다.  상위 클래스에 둔 변수를 하위 클래스로(혹은 그 반대로) 옮기려면, 연쇄 효과를 감수해야 합니다.  설령 옮기지 않더라도, 하위 클래스에게 필요없는 상위 클래스의 변수는 괜히 메모리와 캐시 라인을 낭비합니다.  게다가 필요없는 변수와 엮여 있는 함수도 노출됩니다.
2. 하위 클래스에서 멤버 변수/함수를 선언할 때마다 상위 클래스를 살펴야 합니다.  키워드 virtual이 붙지 않은 함수를 재정의*override*하려 했거나 [fragile base class](https://en.wikipedia.org/wiki/Fragile_base_class) 같은 실수를 범할 수 있기 때문입니다.
3. 'is-a' 관계에 줄곧 상속을 쓰다 보면, 동시에 여러 클래스를 상속해야 할 처지에 놓입니다.  다중 상속은 문제 1과 2가 더 꼬입니다.
4. 코드를 반복하지 않기 위해 상속했다가 오히려 반복할 수 있습니다.  위 문제들은 덤입니다.   
  상속을 쓰지 않고는 유지보수하기 힘들다면 모르겠습니다.  다만, 다른 이유로 상속을 쓰기엔 다른 좋은 대안이 있습니다.  굳이 'is-a' 관계를 코드에 나타내고 싶다면 클래스 이름, 이름공간, 파일 디렉토리로도 할 수 있습니다.  반복되는 코드는 모듈로 떼어내면 여러 클래스에서 쓸 수 있습니다.

**#키워드 final** **#devirtualize**   
  상속을 지양하므로 키워드 final을 애용합니다.   
  이것은 컴파일러가 devirtualize하도록 돕기도 합니다.  이때, 키워드 virtual을 붙이지 않습니다.

**#키워드 virtual**   
  언젠가 상속될 수도 있는 클래스라도 미리 키워드 virtual을 붙여놓지 않습니다.  괜히 vtable을 만들어 메모리를 낭비할 이유가 없기 때문입니다.  키워드 virtual을 붙이지 않아 생기는 실수는 키워드 override로 예방합니다.

**#키워드 override**   
  상위 클래스의 멤버 함수를 재정의하려는 멤버 함수엔 항상 키워드 override를 붙입니다.  이것으로, 키워드 virtual이 붙지 않은 멤버 함수를 재정의하려고 하거나 비슷한 시그니처 때문에 재정의했다고 착각하는 실수를 막을 수 있습니다.  순수 가상 함수를 정의한 멤버 함수에도 키워드 override를 붙입니다.  코드가 일관되고 다른 멤버 함수와 구별할 수 있기 때문입니다.   
( [*dlls/Game/scene/*](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game/scene) 아래 헤더 파일들 )

**#씬*scene* 계층** **#추상화**   
<img src="https://user-images.githubusercontent.com/43042411/76996394-ca664e00-6994-11ea-9f02-740c93d00dbd.png"></img>
  dynamic_cast를 쓰지 않아 씬 계층이 단순하고 게임 루프가 느리지 않습니다.   
  클래스 ::scene::inPlay::InPlay와 ::scene::online::Online은 ::scene::Intro와 ::scene::MainMenu처럼 인터페이스 ::scene::IScene의 구현이지만 씬이 아닙니다.  씬 매니저까지 나와서 처리할 필요가 없는 것들을 맡긴 간이 씬 매니저입니다.  읽고 쓰고 분업하기 쉽게 추상화한 것입니다.   
( [*dlls/Game/scene/*](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game/scene) 아래 헤더 파일들 )

**#위임*delegation***   
  간이 씬 매니저 ::scene::online::Online은 자신이 다루는 씬들에게 위임됩니다.  서버와 통신하기 위한 스레드와 전역변수를 소스 파일 *::scene::online::Online.cpp*에만 선언, 정의했기 때문입니다.  일종의 정보 은닉입니다.   
  인스턴스를 사용하는 도중 지우거나 재귀 호출할 우려가 있으므로 자신을 통째로 위임하지 않도록 고칠 예정입니다.   
( [*dlls/Game/scene/online/*](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game/scene/online) 아래 헤더 파일들과 *Online.cpp* )

**#의존*dependency* 관계** **#편한 디버그** **#x64 호출 규약** **#Aggregation 관계**   
  의존 관계를 선호합니다.  인스턴스를 그때그때 레퍼런스 매개변수로 넘기려고 합니다.  디버그할 때 어떤 인스턴스가 어디에 쓰이는지 쉽게 보이기 때문입니다.  x64 호출 규약*calling convention*상 4 개의 매개변수까진 레지스트리에 넘기므로 성능도 얻습니다.  레퍼런스를 쥐고 있게 하거나 전역 포인터로 넘기는 것은 선호하지 않습니다.   
  하지만 Aggregation 관계가 두 곳 있습니다.  여러 씬들이 인스턴스를 공유하려는데 인터페이스를 수정하고 싶지는 않아서 한 곳에 생겼고, 콘솔로 호출하는 함수들을 컨테이너 하나에 담기 위해 타입을 통일하다 다른 한 곳에 생겼습니다.   
( [*dlls/Game/scene/inPlay/* 아래 헤더 파일들에 선언된 sf::Drawable 멤버 레퍼런스](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/inPlay/Ready.h#L20), [*exes/Engine/Command.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/exes/Engine/Command.h) )

**#RTTI**   
  굳이 쓰지 않아도 되고 성능 손해까지 있지만 연습 삼아 써봤습니다.   
( [*dlls/Game/scene/Playing.cpp:974* 키워드 typeid](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/inPlay/Playing.cpp#L974), [*dlls/Game/scene/IScene.h:34* 순수 가상 함수 currentScene()의 정의](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/Intro.cpp#L139) )

**#인스턴스 카운팅**   
  일부 클래스의 총 인스턴스 수를 제한했습니다.  싱글턴 패턴을 쓰지 않았습니다.   
( [일부 헤더 파일의 static bool IsInstantiated](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/Intro.h#L10) )

**#매크로 상수 없음** **#const와 constexpr**   
  매크로 상수를 쓰지 않습니다.  디버그 창에 뜨지 않기 때문입니다.  그래서 const나 constexpr로 상수를 만듭니다.  주소에 접근하지만 않으면 메모리에 상주하지도 않습니다.

**#전역 변수**   
  **#의존 관계**에서 설명했듯 전역 변수를 좋아하지 않습니다.  하지만 로그, 콘솔, 사운드 등은 편하게 전역 변수로 다루어도 디버그하기 어렵지 않습니다.  이벤트/메시지 큐도 이 게임과 달리 전역 변수로 다루어도 문제 없을 것입니다.   
  전역 변수를 모아 관리할 수 있고 의존성 주입이 되는 서비스 로케이터 패턴을 씁니다.  싱글턴 패턴은 쓰지 않습니다.   
( [*exes/Engine/ServiceLocator.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/exes/Engine/ServiceLocator.h), [*dlls/Game/ServiceLocatorMirror.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/ServiceLocatorMirror.h) )

**#가시성** **#접근 한정자**   
  구조체라도 public을 명시하고 클래스라도 private을 명시합니다.  그렇지 않으면, 볼 때마다 어떤 접근한정자인지 생각하느라 피로가 쌓이기 때문입니다.   
  **#protected**도 참고해주십시오.

**#정보 은닉** **#함수 이름** **#추상화**   
  멤버 변수의 비const 레퍼런스를 반환하는 getter 함수는 setter 함수이기도 하다는 것에 주의해야 합니다.  기존 setter 함수가 한 줄 짜리라면 쉽게 눈에 띄지만, 그렇지 않다면 멤버 변수 하나에 대해 서로 다른 setter 함수를 둘 수 있기 때문입니다.   
  함수 이름은 어떻게 동작하는지가 아니라 결국 하고자 하는 게 뭔지를 나타냅니다.  함수를 사용하는 사람은 어떻게 동작하는지 신경쓰고 싶어하지 않습니다.  어떻게 동작하는지 알려야 한다면 주석을 답니다.   
( [*dlls/Game/ui/PlayView.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/ui/PlayView.h) )

**#함수의 입도*granularity***   
  함수 하나가 여러 기능을 맡지 않습니다.  여러 기능 중 하나만 필요할 때가 닥치어서야 이 함수를 여러 함수로 쪼개면, 연쇄 효과를 감수해야 합니다.  쪼개지 않으면, 기능이 겹치는 함수를 만들어야 합니다.

**#함수≠코드 번들**   
  단지 코드들을 묶어 놓기 위해 함수로 만들지 않습니다.  반환 값과 매개변수가 없는 함수를 호출해도, 새 서브루틴에 접근하고 스택 프레임을 찍는 비용이 듭니다.  인라인 함수는 호출 비용이 없지만, 10줄 안팎의 한계가 있고 헤더 파일이 뚱뚱해집니다.  코드들을 묶는 건 unnamed scope나 주석으로 충분합니다.  

**#멤버 변수의 선언 순서** **#패딩** **#초기화 리스트*initializer list***   
  멤버 변수의 크기가 작은 것부터 선언하여 패딩을 줄입니다.  아무리 대용량 메모리가 보급되었다고 하더라도 캐시 라인까지 낭비할 수는 없습니다.   
  초기화 리스트 순서 역시 선언 순서와 맞추어 컴파일러가 최적화하도록 돕습니다.

**#멤버 변수 이름** **#접두사** **#접미사**   
  멤버 변수의 이름 앞에 알파벳 소문자 m을 붙입니다.  어디에서 멤버 변수의 값이 바뀌는지 IDE에 의존하는 것보다 더 쉽게 알 수 있습니다.   
  레퍼런스나, 연산 반복을 피하기 위해 값을 임시로 저장해두는 멤버 변수의 이름 뒤엔 특수문자 _도 붙입니다.  이렇게 인스턴스의 상태인 보통의 멤버 변수와 구분하면 코드를 읽기 쉽습니다.   

**#unnamed scope**   
  이름이 같은 지역 변수를 선언해도 컴파일러가 알아서 처리해주지만, 일부 지역 변수는 unnamed scope로 수명을 명시했습니다.  단, unnamed scope 때문에 인스턴스를 만들고 지우기를 반복한다면, unnamed scope를 쓰지 않습니다.  인스턴스를 만드는 것도 비용이 들기 때문입니다.

**#늦은*lazy* 지역 변수 선언**   
  지역 변수를 서브루틴의 머리에 모아 두지 않습니다.  그렇지 않으면, 예외 처리 등으로 early exit할 때 괜히 지역 변수를 만들어 매몰 비용이 생기기 때문입니다.  지역 변수가 쓰이는 곳과 거리가 먼 것도 코드를 읽는데 좋지 않습니다.

**#STL 원소에 임의 접근*random access***   
  std::array와 std::vector의 원소는 연산자 []로 접근합니다.  인덱스를 초과하는지는 손수 검사합니다.  내부에서 검사해주는 멤버 함수 at(...)은 쓰지 않습니다.  std::exception으로 예외 처리해서 느리기 때문입니다.  std::vector는 힙 할당과 병합 때문에 성능 손해가 있어 std::array를 선호합니다.   
  std::unordered_map의 원소는 멤버 함수 find(...)로 접근합니다.  연산자 []는 되도록 쓰지 않습니다.  없는 키를 넣어도 값을 만들어내기 때문입니다.  값을 만들어내기 위해 기본 생성자를 강요한다는 것도 단점입니다.  멤버 함수 at(...) 역시 쓰지 않습니다.

**#배열** **#std::array**   
  스택에 있는 배열을 받는 매개변수로 C 스타일이 아닌 std::array를 둡니다.  크기와 차원을 전달하기 쉽기 때문입니다.

**#시간 복잡도** **#실제 빠르기**   
  단지 자료 구조 중간에 있는 원소를 빼내거나 새로 넣는 경우가 잦다고 연결 리스트를 쓰지는 않습니다.  원소의 크기가 64 바이트 미만이면 SIMD를 쓰지 않아도 배열이 더 빠릅니다.  이 경우에도 단일*singly* 연결 리스트는 배열보다 빠르지만, 직전 원소를 따로 다뤄야 해 코드가 길고, 자료 구조 가장 뒤에 원소를 넣기에도 부적합합니다.   

**#문자열 리터럴**   
  문자열 리터럴은 (const/constexpr) char[]나 std::string으로 받습니다.  const char\*로 받은 문자열 리터럴은 메모리에 남아 보안에 해가 되기 때문입니다.

**#문자열을 받는 매개변수**   
  nullptr을 걸러낼 수 없는 char\*보다 const char (&)[N]를, 문자열 리터럴이 메모리에 남을 수 있는 const char (&)[N]보다 std::string을 선호합니다.  char\*이 쓰인 곳은 재귀 함수와 윈속 send 함수뿐입니다.   
( [*staticLibs/Lib/Hash.h:12*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/staticLibs/Lib/Hash.h#L12), [*Socket.h*:78](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/staticLibs/Lib/Socket.h#L78) )

**#문자열 해싱** **#보안** **#성능**   
  보안과 성능을 위해 문자열을 해싱해 다룹니다.  문자열을 해싱해 비교하면 ::strcmp(...) 등으로 비교하는 것보다 유의미하게 빠릅니다.

**#인스턴스 복사 줄이기**   
  예로, std::unordered_map는 멤버 함수 try_emplace(...)와 emplace(std::piecewise_construct, std::forward_as_tuple(...)...)를 써서 인스턴스가 불필요하게 복사되지 않도록 합니다.

**#복사 생성자** **#이동 생성자** **#키워드 delete**   
  되도록 건들지 않습니다만, 복사/이동 생성자가 의도와 다르게 작동할 우려가 있으면 없애둡니다. 

**#인스턴스 재활용**   
  그래픽 인스턴스처럼 덩치가 크거나 소켓처럼 핸들을 얻는 데 비용이 크면, 가능한 한 기존 인스턴스를 재활용합니다.   
( [*dlls/Game/model/Tetrimino.h:118*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/model/Tetrimino.h#L118), [*dlls/Game/ui/NextTetriminoPanel.h:71*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/ui/NextTetriminoPanel.h#L71) )

**#NRVO**  
  RVO을 위해 R-Value만 반환하거나 Named Return Value만 반환할 뿐, 한 함수에서 둘을 혼용하지 않습니다.

**#범위 기반*range-based* for 반복문**   
  범위 기반 for 반복문을 선호합니다.  C 스타일 for 반복문보다 빠르기 때문입니다.   
  std::for_each(...)는 C 스타일 for 반복문보다 느려, 반복자*iterator*를 쓰는 for 반복문은 가장 느려 쓰지 않습니다.  범위 기반 for 반복문도 내부에서 반복자를 쓰는데도 불구하고 그 차이가 큽니다.

**#enum class**   
  enum class 타입은 enum 타입과 달리 스코프*scope*를 명시하도록 강요하므로 더 안전하게 코딩할 수 있습니다.   

**#키워드 inline**   
  오버로드한 연산자와 소스 파일에 선언, 정의된 짧은 함수를 인라인으로 만들려면 키워드 inline을 명시해야 합니다.  프로젝트 설정만으로는 인라인으로 만들 수 없습니다.  인라인 여부는 디스어셈블리에 call 인스트럭션이 있는지 아닌지를 보면 쉽게 알 수 있습니다.

**#C 스타일 캐스트**   
  static_cast<T>, reinterpret_cast<T>를 쓰지 않고 (T), (T\*)처럼 C 스타일로 캐스트합니다.  차이도 없고 읽고 쓰기도 쉽기 때문입니다.

**#switch 분기문**   
  if 분기문보다 switch 분기문을 선호합니다.  case들을 오름차순으로 정렬하면 컴파일러가 최적화해주기 때문입니다.   
  Default case가 있으면 안 되는 경우, 디버그 모드에선 __debugbreak()(x86의 __asm { int 3 })를 두어 오류를 잡습니다.  릴리즈 모드에선 __assume(0)을 두어 컴파일러가 최적화하도록 합니다.

**#SFINAE** **#std::enable_if**   
  SFINAE로 템플릿이 특정 타입만 받도록 강제할 수 있습니다.  인텔리센스 덕분에 컴파일하지 않고도 추론이 어떤지를 알 수 있습니다.  static_assert는 이렇지 않습니다.   
( [*staticLibs/Lib/ScriptLoader.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/staticLibs/Lib/ScriptLoader.h) )

**#키워드 friend**   
  키워드 friend가 항상 정보 은닉을 깨는 건 아닙니다.   
( [*staticLibs/GameLib/IGame.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/staticLibs/GameLib/IGame.h), [*dlls/Game/ServiceLocatorMirror.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/ServiceLocatorMirror.h)와 [*Game.cpp*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/Game.cpp) )

**#goto**   
  두 겹 이상의 스코프를 빠져나가는 경우에만 goto를 허용합니다.  키워드 break로는 이것을 할 수 없는데다 goto 문이 읽기도 쉽기 때문입니다.   
( [*dlls/Game/scene/MainMenu.cpp:999*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/MainMenu.cpp#L999) )

**#예외 처리**   
  예외 처리는 빠르고 읽기 쉬운 if 문으로 처리합니다.  try-catch 블록은 쓰지 않습니다.

**#빌드 타임 링킹 라이브러리**   
  .obj 파일도 바뀐 코드가 없다면 다시 컴파일하지 않습니다.  그렇지만 앞으로도 코드가 바뀌지 않는 모듈은 라이브러리로 떼어놓는 것이 다시 컴파일하지 못하도록 하는 확실한 방법이고, 커플링을 막고 여러 프로젝트에서 재사용하기도 좋습니다.   
  런타임 링킹 방법들과 달리 빌드 타임 링킹 방법이 갖는 장점은 바이너리 파일을 프로세스로 올릴 때 라이브러리가 필요하지 않다는 것입니다.  대신 똑같은 라이브러리가 여러 프로세스마다 있는 셈이라 메모리 낭비일 수 있습니다.  출력 파일 .lib가 런타임 링킹 방법들보다 훨씬 커지기도 합니다.   
( [*staticLibs/Lib/* 프로젝트](https://github.com/Mynsu/Sirtet_SFML/tree/master/staticLibs/Lib) )

**#헤더 파일만 있는 라이브러리**   
  헤더 파일만 공유하더라도 그냥 포함만 하지 않고 라이브러리에 둡니다.  인텔리센스가 구문 분석을 못하기 때문입니다.   
( [*staticLibs/GameLib/* 프로젝트](https://github.com/Mynsu/Sirtet_SFML/tree/master/staticLibs/GameLib) )

**#런타임 링킹 라이브러리** **#.dll**   
  대개 여러 프로세스에서 공유할 수 있다는 점 때문에 런타임 링킹 라이브러리, 즉 .dll 파일을 만들지만, 이 게임은 아닙니다.  엔진으로부터 Mod, 확장팩, 게임 컨텐츠를 따로 떼어내 개발하기 위해 .dll 파일을 만들었습니다.   
  .dll 파일을 .lib 파일(빌드 타임 링킹 라이브러리의 출력 파일이 아닙니다)과 함께 쓰지 않았습니다.  처음엔 함께 썼습니다만 더욱 추상화하기 위해 지금의 방법으로 옮겼습니다.  런타임 중 해제하고 로드하기 위해 옮긴 것이 아닙니다.   
( [*dlls/Game/* 프로젝트](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game) )

**#씬 생성** **#의존성 주입 vs. 일원화**   
  처음엔 다음 씬을 생성하는 걸 각 씬에게 맡겼습니다.  그런데 콘솔이나 스크립트로 원하는 씬을 열려면 씬 매니저도 씬을 생성할 수 있어야 했습니다.  두 방법을 혼용하니 코드가 난잡해졌고 결국 씬 매니저에게 일임했습니다.  대신 씬을 추가할 때마다 분기문으로 관리하게 되었습니다.   
( [*dlls/Game/scene/SceneManager.h*의 멤버 함수 update(...)](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/SceneManager.h#L27)와 [setScene(...)](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/SceneManager.cpp#L44) )

**#키워드 auto** **#C++ 1y**   
  단지 타입이 길다고 키워드 auto를 쓰진 않습니다.  바로 근처 코드에서 쉽게 유추할 수 있어야 씁니다.  코드를 읽는 데 방해되므로 웬만하면 쓰지 않습니다.  이 저장소에서는 반복자, structured binding, utf-8 문자열 리터럴을 받는 데 쓰였습니다.

**#Uniform 초기화** **#C++ 1y**   
  Uniform 초기화는 매개변수가 std::initializer_list인 생성자에 따라 의도치 않은 동작을 할 수 있기 때문에 쓰지 않습니다.  ( )로 초기화하는 것이 중의적이라면 =로 초기화합니다.  이 저장소에서 { }로 초기화한 것은 집합*aggregation* 초기화입니다.

**#람다 표현식**   
  많은 지역 변수들을 함수에 넘기기엔 매개변수가 너무 많고, 한 구조체로 묶어 넘기기엔 억지고, 전역으로 옮기는 것은 지양하므로(**#의존 관계** 참고) 람다 표현식을 썼습니다.  다른 스레드에서 돌릴 일회용 함수도 람다 표현식으로 정의했습니다.   디커플링을 위해 캡쳐는 항상 명시합니다.   
( [*exes/QueueServer.cpp:269*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/QueueServer/QueueServer.cpp#L269), [*Server.exe:124*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/Server/Server.cpp#L124), [*dlls/Game/scene/online/Waiting.cpp:424*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/online/Waiting.cpp#L424) )

**#루아*Lua* 스크립트**   
  기획자와 아티스트가 부담없이 수정하고 적용할 수 있도록, 데이터와 리소스를 루아 스크립트로 다룹니다.   
로직은 빠르고 디버깅이 쉬워야 하므로 C++에서 다룹니다.

**#SFML**    
  SFML은 SDL처럼 오픈 소스 멀티미디어 라이브러리지만 레퍼런스가 적습니다.  그럼에도 SFML을 쓴 건 SDL과 달리 C++로 작성되었기 때문입니다.  C++와 OOP의 좋은 예를 뜯어보며 추상에서 구체로 학습할 수 있습니다.

**#콘솔**   
<a href="https://youtu.be/uPx0DgMIeoQ" target="_blank"><img src="https://user-images.githubusercontent.com/43042411/76969660-0508c000-696e-11ea-897a-5b9b868422ae.jpg" width="600" height="337" border="0"></a> *( 유투브 링크 )*   
  명령어와 함수를 매핑하여 런타임 중에 콘솔로 여러 시도를 해볼 수 있습니다.  현재는 스크립트를 새로고침하거나, 원하는 씬으로 이동하거나, GUI가 미완성일 때를 대비한 방 생성/입장 명령어들이 등록되어 있습니다.   
  명령을 비동기로 수행하므로 공유 데이터를 관리해야 합니다.   
( [*exes/Engine/Console.h*](https://github.com/Mynsu/Sirtet_SFML/blob/master/exes/Engine/Console.h) )

**#로그**   
  현재 콘솔에만 출력하고 파일로는 출력하지 않습니다.

**#수학** **#벡터** **#선형 보간**   
  UI 애니메이션에 2차원 벡터 연산과 선형 보간이 쓰였습니다.   
( [*dlls/Game/scene/online/InLobby.cpp:952, 1375*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/online/InLobby.cpp#L1375) )

**#TCP/IP** **#여기부터 네트워크&시스템 프로그래밍**   
  UDP는 wouldblock 때 패킷이 유실될 가능성이 있어 쓰지 않았습니다.

**#전이중*full-duplex***   
  거의 동시에 여러 번 보내고 받을 수 있도록 여러 개의 WSAOVERLAPPED 구조체를 씁니다.   
  한 개의 구조체로는 보내기나 받기를 완료한 뒤에야 받기나 보내기를 걸어둘 수 있기 때문입니다.

**#온라인** **#대기열 서버** **#메인 서버**   
  서버는 단 둘, 대기열 서버와 메인 서버가 있습니다.   
  데모답게 중개를 위한 Redis 서버나 계정 관리를 위한 RDBMS 서버는 없습니다.   
  클라이언트가 서버에 접속할 때 악수와 함께 메시지를 보내더라도 서버가 무시합니다.  그렇지 않으면 서버가 메시지를 하염없이 기다리는 문제가 생길 수 있습니다.   
  서버의 부하를 덜기 위해 서버가 accept를 완료한 후에야 클라이언트가 접속합니다.   
<img src="https://user-images.githubusercontent.com/43042411/76689270-8f53da00-6677-11ea-9d8e-ad9e4df90409.png"></img>   
*( 시퀀스 3부터 그린 다이어그램 )*
1. 대기열 서버가 클라이언트(혹은 피어*peer*)로서 메인 서버에 접속합니다.   
1-1. 대기열 서버가 멈추더라도 다시 켜면 메인 서버에 접속할 수 있습니다.
2. 대기열 서버가 메인 서버에게 자신이 대기열 서버임을 알립니다.  메인 서버는 특정 클라이언트를 대기열 서버로 간주합니다.
3. 클라이언트가 대기열 서버에 접속합니다.
4. 클라이언트가 대기열 서버에 약속한 해시 값을 보냅니다.  대기열 서버는 해시값, 즉 초대장을 보고 가짜 클라이언트가 아닌지, 서버들과 버전이 같은지를 확인합니다.
5. 클라이언트가 주어진 시간 내에 시퀀스 4를 통과하고 메인 서버에도 자리가 있으면, 대기열 서버가 클라이언트와 메인 서버에 똑같은 티켓을 보냅니다.   
5-1-1. 클라이언트가 주어진 시간 내에 시퀀스 4를 통과했으나 메인 서버에 자리가 없으면, 대기열 서버는 클라이언트에 대기 번호를 발급하고 메인 서버에 자리가 났는지 주기적으로 물어봅니다.   
5-1-2. 메인 서버에 자리가 나면, 대기 번호 0 클라이언트에게 시퀀스 5를 수행합니다.   
5-2. 클라이언트가 주어진 시간 내에 시퀀스 4를 통과하지 못하면, 대기열 서버가 클라이언트의 접속을 끊고 시퀀스를 종료합니다.
6. 대기열 서버가 티켓을 보낸 클라이언트와 접속을 끊습니다.
7. 클라이언트가 메인 서버에 접속합니다.
8. 클라이언트가 대기열 서버로부터 받은 티켓을 메인 서버에 에코합니다.
9. 메인 서버가 클라이언트로부터 받은 티켓이 대기열 서버로부터 받은 티켓과 일치하면, 클라이언트의 접속을 유지합니다.   
9-1. 일치하지 않으면 메인 서버가 클라이언트의 접속을 끊습니다.

**#IOCP** **#Completion routine** **#서버**   
  서버의 소켓 입출력에 IOCP를 썼습니다.  메인 스레드는 게임 로직만 담당했습니다.  IOCP 때문에 completion routine을 비동기 호출하지 못한다는 점이 아쉽습니다.   
  클라이언트는 IOCP를 쓰지 않고 completion routine을 비동기 호출합니다.

**#버퍼 복사하지 않기** **#대기열 서버**   
  대기열 서버가 accept 완료한 소켓들의 O/S 층 버퍼를 없애 데이터를 직접 받습니다.  그래서 O/S 층 버퍼와 애플리케이션 층 버퍼 사이에 복사가 일어나지 않습니다.  대기열 서버는 버퍼가 필요할 만큼 무거운 작업을 하지 않기 때문에 가능한 일입니다.  대신 안정적으로 통신하도록 클라이언트에 있는 대기열 서버 소켓의 O/S 층 버퍼는 없애지 않았습니다.   
  메인 서버는 O/S 층 버퍼를 건들지 않고 있습니다.  이 개발 환경에서 받기 버퍼를 없애면, 클라이언트가 보낸 데이터를 메인 서버가 간혹 받지 못하기 때문입니다.  그리고 클라이언트의 받기 버퍼가 가득찼을 때 서버에 보내기 버퍼가 없으면, 클라이언트가 이상한 값을 받기 때문입니다.   
( [*exes/QueueServer/QueueServer.cpp:177*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/QueueServer/QueueServer.cpp#L177) )

**#백로그** **#::AcceptEx(...)**   
  백로그만큼 ::AcceptEx(...)를 걸어 두었습니다.   
  최근 걸어둔 소켓부터 accept가 완료되기 때문에, TCP timed wait delay 상태에 있는 소켓을 걸어 두지 않도록 유의합니다.   
( [*exes/QueueServer/QueueServer.cpp:245*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/QueueServer/QueueServer.cpp#L245), [*exes/Server/Server.cpp:90*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/Server/Server.cpp#L90) )

**#접속** **#Conditional accept**   
  소켓 옵션으로 conditional accept를 주어, 서버가 accept를 완료해야 클라이언트가 접속할 수 있습니다.  이렇게 하지 않으면 클라이언트가 접속을 시도하는 것만으로 서버에 부하를 줍니다.   
( [*exes/QueueServer/QueueServer.cpp:191*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/QueueServer/QueueServer.cpp#L191), [*exes/Server/Server.cpp:46*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/Server/Server.cpp#L46) )

**#소켓 재활용** **#DisconnectEx(...)**   
  **#인스턴스 재활용**에서 언급한 것처럼 O/S로부터 소켓 핸들을 얻는 것은 비용이 큽니다.  그래서 접속을 끊을 땐 ::DisconnectEx(...)를 써 소켓을 재활용합니다.  보내기, 받기를 걸어 두다 실패한 소켓만 새것으로 교체합니다.  실패한 소켓들은 ::DisconnectEx(...)도 실패하므로 재활용할 수 없기 때문입니다.   
  재활용하든 새것으로 교체하든 한 가지 주의해야 할 것이 있습니다.  재활용하거나 새것으로 교체하기 전에 걸어 두었던 작업이 그 후 뒤늦게 이벤트를 알립니다.  이것을 무시해야 합니다.

**#스트레스 테스트**   
  20년 3월 15일 현재, 클라이언트 100개까지 통과합니다.   

**#클라이언트** **#블로킹*Blocking* 소켓** **#멀티스레드** **#graceful shutdown**   
  클라이언트에는 블로킹 소켓을 썼습니다.  멀티스레드 다루는 걸 연습하고 싶었기 때문입니다.  클라이언트를 만들기 시작했을 때는 보내는 것도 블로킹이었으나, 지금은 받는 것만 블로킹이고 보내는 것은 Overlapped I/O입니다. 코드가 복잡했고 오작동이 잦았기 때문입니다.   
  보내거나 받을 때마다 스레드를 만들어 주진 않습니다.  컨텍스트를 스위칭하는 비용이 크고 스레드가 시작되는 타이밍이 들쑥날쑥하기 때문입니다.   
  블로킹이 풀려야 소켓을 닫습니다.  소켓을 닫아 블로킹을 강제로 풀지 않습니다.   
( [*dlls/Game/scene/online/Online.cpp*](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/scene/online/Online.cpp) )

**#스트림 헤더**   
  스트림의 머리에 의미를 갖는 ID(혹은 태그)와 헤더를 제외한 스트림의 길이가 붙습니다.  ID에 2~3 바이트 정수를, 길이에 2 바이트 정수를 씁니다.  스트림의 꼬리는 표기하지 않습니다.   
( [_staticLibs/GameLib/Common.h:135_](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/staticLibs/GameLib/Common.h#L135) )

**#가짜 클라이언트 감지** **#해시 salt** **#키 스트레칭**   
  **#대기열 서버**에서 '초대장'이 언급됩니다.  초대장은 현재 시간과 salt와 키 스트레칭으로 얻은 해시 값이면 충분합니다.  암복호화 알고리즘을 쓰지 않아 부하가 덜합니다.   
( [*dlls/Game/scene/online/Waiting.cpp:17*](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/scene/online/Waiting.cpp#L17) )

**#클라이언트와 서버가 공유하는 모델 애셋*asset*** **#디버그 일기**   
  서버를 만들기 시작했을 땐 클라이언트가 쓰던 모델 애셋을 그대로 가져와 썼었습니다.  곧, 렌더링에 쓰이는 멤버 변수/함수는 서버에게 불필요하다는 걸 알아챘습니다.  그래서 서버의 부하를 덜기 위해 필요없는 부위를 뺀 서버용 모델 애셋을 만들었습니다.   
  서버용 모델 애셋을 따로 만들더라도 개발 막바지에 했어야 했습니다.  비효율적으로 따로따로 수정하다보니 같아야 할 코드가 달라지는 등 실수가 나왔기 때문입니다.   
( [_dlls/Game/model/_](https://github.com/Mynsu/Sirtet_SFML/tree/master/dlls/Game/model)과 [*exes/Server/*](https://github.com/Mynsu/Sirtet_SFML/tree/master/exes/Server) 아래 *Tetrimino.h*와 *Stage.h* )

**#클라이언트와 서버의 동기화**   
  게이머가 테트리미노를 움직이기 위해 입력하자마자 클라이언트가 그 움직임을 적용합니다.  거의 동시에 클라이언트는 서버에도 그 움직임을 전달합니다.  입력은 서버에서 검증*validation*한 다음 클라이언트에 적용하는 것이 정석입니다.  하지만 이 게임은 게이머가 클라이언트를 왜곡해도 자신만 손해기 때문에 의도적으로 정석을 따르지 않습니다.  따라서 서버가 입력을 검증하는 동안 클라이언트가 애니메이션을 보여주며 응답이 빠른 척할 필요가 없습니다.   
( [_dlls/Game/ui/PlayView.cpp:201_](https://github.com/Mynsu/Sirtet_SFML/blob/master/dlls/Game/ui/PlayView.cpp#L201) )   
  반면, 게이머가 테트리미노 낙하 속도를 못된 방법으로 낮추면 클라이언트가 접속 종료됩니다.  클라이언트와 서버 모두에서 시간을 따로 재어 처리합니다.  역시 낙하 속도를 높히는 것은 게이머 자신에게 손해기 때문에 처리하지 않습니다.  대신 다음 테트리미노가 스폰되는 시간을 서로 동기화합니다.   
( [_dlls/Game/ui/PlayView.cpp:148_](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/dlls/Game/ui/PlayView.cpp#L148), [_exes/Server/Room.cpp:45_](https://github.com/Mynsu/Sirtet_SFML/blob/9a5e461624dd15256a1f22c75fd294aef88ab21d/exes/Server/Playing.cpp#L45) )

**#디버그 모드에서 릴리즈 모드로** **#프로파일링** **#디버그 일기**   
  디버그 모드에서 릴리즈 모드로 바꾸고 난 뒤 이슈가 하나 있었습니다.  클라이언트가 메인 서버와 통신하다가 끊기는 이슈였습니다.  원인을 찾기 위해 프로젝트 설정을 소거해나갔습니다.  결국 메인 서버의 CRT가 /MDd가 아니라서 생긴 이슈임을 알아냈습니다.  릴리즈 모드의 기본값이 /MD이므로 원인은 DLL 여부가 아니라 디버그 여부라고 판단, 메인 서버를 /MTd로 빌드했습니다.  그런데 아뿔싸!  이젠 /MDd로 빌드한 클라이언트는 통신이 잘 되고 /MD로 빌드한 클라이언트는 안 되는 것이었습니다.   
  다시 처음으로 돌아왔습니다.  '메인 서버가 느리다'는 겉보기부터 풀어 나갔습니다.  아니나다를까 릴리즈 모드로 빌드한 메인 서버가 방 하나에 클라이언트 둘 이상이 들어오자마자 프레임 당 300 밀리초를 넘기는 것이었습니다.  프로파일링으로 필요없는 WSAOVERLAPPED 구조체를 지우느라 병목이 걸린다는 것을 알아냈습니다.  의도와 달리 게임 루프마다 구조체를 만들기 때문이었습니다.   
  릴리즈 모드로 빌드한 메인 서버가 게임 루프를 한 번 도는 시간이 디버그 모드로 빌드한 것보다 훨씬 짧아서 더 많은 구조체를 만들어냈고 아이러니하게도 더 느려진 것입니다.  릴리즈 모드 덕분에 버그를 찾은 셈입니다.

**#OpenMP**   
  반복문에 OpenMP를 써봤다가 훨씬 더 느려 더이상 쓰지 않습니다.

**#이동 생성자** **#템플릿 특수화** **#유니버설 레퍼런스** **#퍼펙트 포워딩**   
  쓸 기회가 없거나 더 쉬운 다른 방법이 있어 쓰지 않았습니다.

**#루프 언롤링**   
  좋아하지만 이 저장소에선 쓰지 않았습니다.

**#메소드 체이닝**   
  입출력 스트림, 문자열 스트림 외엔 쓰지 않습니다.  반환 값이 없는 함수만 체이닝하는 것도 일관된 코드가 아니고, 메소드 체이닝 때문에 코드가 오히려 지저분하기 때문입니다.

**#로컬 게임 개발** **#온라인 게임 개발** **#비교 체험**   
  **#클라이언트와 서버가 공유하는 모델 애셋**에서 겪은 것말고도 여럿 있습니다.  예로, 로컬 게임과 달리 온라인 게임은 입출력과 게임 로직 사이에 있는 시간 차이를 다루어야 합니다.  또, 온라인 게임은 로컬 게임을 기반, 입력부, 로직부, 출력(렌더)부로 나누어 로직부만 서버로 옮긴 것이라 여길 수도 있겠습니다.

마지막으로 수정한 날은
----------------------
2020년 4월 12일
