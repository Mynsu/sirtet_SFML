Sirtet
======
예, 맞습니다.  테트리스입니다.
제가 테트리스를 만든 이유는
1. 심사원께 익숙한 게임 코드라면 피로 물질이 덜 쌓일테고,
2. 3D 그래픽스 API, 셰이더, 쿼터니언/텐서/미적분이 없어 심사원께서 코드 '기본'만 보기 좋고,
3. [**여기**](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/your-first-step-to-game-development-starts-here-r2976/)[**저기**](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/how-do-i-make-games-a-path-to-game-development-r892/)에서 추천한 게임들 중 유일하게 게임 플레이 로직이 머릿속에 그려지지 않았으며,
4. 하고 싶지 않은 게임을 끝까지 만들어 낼 수 있는지 제 자신이 궁금했기
때문입니다.

 
환경
----
C++ 17, 비주얼 스튜디오 2017, SFML 2.5.1, Lua 5.3.5 and 윈도우즈 10.


#스트레스 테스트
현재 클라이언트 100개까지만 테스트했습니다.

(그림;시퀀스 다이어그램)#대기열 서버 #메인 서버
서버는 둘, 대기열 서버와 메인 서버를 두었습니다.
클라이언트가 접속과 동시에 메시지를 보내더라도 서버가 이 메시지를 받지 않도록 했습니다.  클라이언트가 메시지를 안 보낼 경우 서버상 이 클라이언트에 대응하는 소켓이 메시지를 기다리는 문제가 발생하기 때문입니다.
서버의 부하를 덜기 위해 서버가 accept를 완료한 후에야 클라이언트가 접속하도록 했습니다.

1. 대기열 서버가 클라이언트(혹은 피어peer)로서 메인 서버에 접속합니다.
1-1. 대기열 서버가 멈추더라도 다시 켜면 메인 서버에 접속할 수 있습니다.
2. 대기열 서버가 메인 서버에게 대기열 서버로서의 증표를 보냅니다.  메인 서버는 증표를 보낸 클라이언트를 대기열 서버로 간주합니다.
3. 클라이언트가 대기열 서버에 접속합니다.
4. 클라이언트가 대기열 서버에 임의의 해시 값을 보냅니다.  대기열 서버는 이 초대장을 보고 클라이언트가 변조되지 않았는지, 서버들과 버전이 같은지를 확인합니다.
5. 클라이언트가 시간 내에 4를 통과하고 메인 서버에도 자리가 있으면, 대기열 서버가 클라이언트와 메인 서버에 똑같은 티켓을 보냅니다.
5-1-1. 클라이언트가 시간 내에 4를 통과했으나 메인 서버에 자리가 없으면, 대기열 서버는 클라이언트에 대기 번호를 발급하고 메인 서버에 자리가 났는지 주기적으로 물어봅니다.
5-1-2. 메인 서버에 자리가 나면, 대기 번호 0 클라이언트에게 5를 수행합니다.
5-2. 클라이언트가 시간 내에 4를 통과하지 못하면, 대기열 서버가 클라이언트의 접속을 끊습니다.
6. 대기열 서버가 티켓을 보낸 클라이언트와 접속을 끊습니다.
7. 클라이언트가 메인 서버에 접속합니다.
8. 클라이언트가 대기열 서버로부터 받은 티켓을 메인 서버에 에코합니다.
9. 메인 서버가 클라이언트로부터 받은 티켓이 대기열 서버로부터 받은 티켓과 일치하면, 클라이언트의 접속을 유지합니다.
9-1. 일치하지 않으면 메인 서버가 클라이언트의 접속을 끊습니다.

#소켓 재활용 #DisconnectEx
정상적으로 접속을 끊은 소켓은 ::DisconnectEx(...)로 재활용했습니다.  소켓을 새것으로 교체하는 비용이 비싸기 때문이었습니다.  보내기나 받기가 실패한 소켓은 거의 모두 재활용도 실패했기 때문에 이 소켓은 새것으로 교체하도록 했습니다.  이 때 갑작스러운 교체로 생긴 문제들을 마무리하고나서 다시 ::Acceptex(...)를 걸어두었습니다.

#IOCP #Overlapped I/O #Completion Routine
서버의 소켓 입출력에 IOCP를 썼습니다.  게임 로직은 모두 메인 스레드에서 수행토록 했습니다.

#람다 표현식
함수의 인수parameter가 많은 것도 싫고 지역 변수들을 전역으로 옮기기도 싫었을 때와 별도의 스레드에서 돌릴 함수가 일회용일 때만, 캡쳐를 명시한 람다 표현식을 썼습니다.
( exes/QueueServer.cpp:269, Server.exe:122, dlls/Game/scene/online/Waiting.cpp:424 )

#범위 기반 for 반복문
범위 기반range-based for 반복문이 가장 빨라 선호했습니다.  마찬가지로 반복자를 쓰는 C 스타일 반복문은 오히려 가장 느려, 반복자가 필요하지 않으면 쓰지 않았습니다.  <algorithm>의 std::for_each(...)는 C 스타일 반복문보다 느려 쓰지 않았습니다.

#OpenMP
OpenMP가 더 느려 개발 도중 없앴습니다.

#백로그 #::AcceptEx(...)
백로그가 수용할 수 있는 접속 수만큼 ::AcceptEx(...)를 걸어두었습니다.

#접속 #Conditional Accept
클라이언트가 괜히 서버에 부하를 주지 못하도록 소켓 옵션으로 conditional accept를 설정했습니다.
같은 이유로 클라이언트가 변조, 버전 확인을 위한 해시 값을 일정 시간 내에 보내지 않으면 대기열 서버가 연결을 끊도록 했습니다.

#버퍼 쓰지 않기 #소켓 옵션
대기열 서버 리스너와 리스너가 accept한 소켓들의 O/S상 버퍼를 없애 복사하지 않도록 했습니다.  버퍼가 필요할 만큼 무거운 작업을 하지 않기 때문입니다.  대신 클라이언트가 보내기/받기 버퍼를 갖습니다.

#인스턴스 복사 줄이기
try_emplace(...)와 emplace(std::piecewise_construct, std::forward_as_tuple(...)...)를 써서 인스턴스를 불필요하게 복사하지 않도록 했습니다.  std::vector::erase(...)가 복사 생성자를 요구하므로, 이 경우 외엔 모두 복사/이동 생성자를 명시적으로 없앴습니다.  

#선형대수학 #벡터 #선형 보간
UI 애니메이션에 2차원 벡터 연산과 선형 보간이 쓰였습니다.
( dlls/Game/scene/online/InLobby.cpp:956, 1384 )

#변조 클라이언트 감지 #해시 salt #키 스트레칭
클라이언트가 변조되진 않았는지, 버전이 서버들과 같은지를 대기열 서버가 확인토록 했습니다.  비대칭 키를 쓰지 않고, 현재 시간과 salt와 키 스트레칭으로 얻은 해시 값을 썼습니다.

#NRVO
RVO을 위해 R-Value나 Named Return Value 중 하나만 썼을 뿐 섞어쓰지 않았습니다.

#블로킹Blocking 소켓 #윈속
클라이언트에는 블로킹 소켓을 썼습니다.  논블로킹 소켓을 쓰지 않은 이유는 멀티스레드 프로그래밍을 연습하고 싶었기 때문입니다.
개발 도중, 블로킹 소켓을 쓰는 ::send(...) 함수를 overlapped된 ::WSASend(...) 함수와 completion routine으로 교체했습니다.  스레드를 재활용하며 ::send(...) 함수를 쓰니 멀티스레드 프로그래밍 특유의 문제들이 발생했기 때문입니다.  그렇다고 ::send(...) 함수를 쓸 때마다 스레드를 새로 만들어 줄 수는 없었습니다.  스레드를 만드는 것만 해도 비용이 크고, 먼저 만든 스레드가 먼저 돈다는 보장이 없기 때문이었습니다.  받는 데에는 여전히 별도의 스레드를 재활용하며 블로킹 소켓과 ::recv(...) 함수를 썼습니다.
타임아웃을 주어 스레드를 join한 다음 소켓을 닫았습니다.  반대 순서로 소켓을 닫아 블로킹을 푼 다음 스레드를 join할 수도 있었지만, 더 graceful하게 종료했습니다.

#함수를 잘못 사용할 위험 차단
예를 들어, 서버로부터 받은 스테이지를 클라이언트에 적용하면서 함께 취해야할 부대 사항들을 묶어 놓은 함수 1이 있습니다.  그런데 스테이지의 레퍼런스를 넘기는 함수 2까지 있으면, 미래의 자신을 포함한 다른 사용자가 함수 1을 쓰지 않고 함수 2를 쓸 위험이 있습니다.  이런 경우는 없어야 합니다.
( dlls/Game/ui/PlayView.h )

#함수의 입도granularity
함수 하나가 다양한 기능을 맡지 않습니다.  일부 기능만 써야했을 때 이 함수를 다시 여러 함수로 쪼개거나 중복된 기능을 하는 함수를 또 만들어야 했기 때문입니다.

#함수 선언/정의
한 루프 안에 2번 이상 호출하거나 혹은 은닉된 정보에 캡슐화된 함수만 선언/정의됐습니다.  단지 표현식expression들을 묶어둔 함수는 없습니다.  함수는 호출 비용이 작지 않고, 인라인 함수라도 헤더 파일이 더러워집니다.

#전방 선언forward declaration
.h 파일에서 요구하지 않는 이상 클래스를 전방 선언하고 .cpp 파일에 포함하여 순환 포함으로 인한 빌드 에러를 예방했습니다.
( dlls/Game/ui/NextTetriminoPanel.h, PlayView.h, dlls/Game/scene/online/ 이하 헤더 파일들 )

#서버와 클라이언트가 공유하는 모델 애셋
모델 애셋 Tetrimino와 Stage는 클라이언트와 서버 모두에서 쓰입니다.  그런데 서버에서는 렌더에 필요한 부분이 필요하지 않아 라이브러리로 공유하지 않고 따로 두었습니다.  그렇게 해보니 같은 수정을 두 번 씩 반복해야 했고 따로 열어 디버그해야 했습니다.  그래서 지금은 라이브러리로 공유하는 것이 더 낫다고 생각합니다.

#uniform 초기화
uniform 초기화는 std::initializer_list를 인자로 받는 생성자가 의도와 다를 위험이 있기 때문에 쓰지 않았습니다.
( dlls/Game/model/Tetrimino.cpp:8 )

#enum class
enum 형과 달리 스코프를 명시해야 해서 더 안전하게 코드를 작성할 수 있기 때문에 enum class 형을 썼습니다.

#인스턴스 재활용
그래픽 인스턴스처럼 덩치가 크면 재활용하여 비용을 줄였습니다.
( dlls/Game/model/Tetrimino.h:133, dlls/Game/ui/NextTetriminoPanel.h:71 )

#키워드 inline
오버로드한 연산자와 .cpp 파일에 선언/정의된 짧은 함수에만 키워드 inline을 명시했습니다.  명시하지 않으면 컴파일러가 인라인으로 처리하지 않기 때문입니다.  이는 디스어셈블리에 call 인스트럭션 여부로 쉽게 알 수 있습니다.

#C 스타일 캐스트
static_cast<T>, reinterpret_cast<T>를 쓰지 않고 (T), (T*)처럼 C 스타일로 캐스트했습니다.  표현식expression이 지저분하지 않고 차이도 없기 때문입니다.
덧붙여 dynamic_cast<T>와 const_cast<T>는 비싸거나 필요가 없어 쓰지 않았습니다.

#switch 분기문
if 분기문보다 switch 분기문을 선호했습니다.  case들을 오름차순으로 정렬하면 컴파일러 최적화가 가능하기 때문입니다.
default case가 없는 경우 디버그 모드에선 __debugbreak()를 두어 코드에 안전함을 기하고 릴리즈 모드에선 __assume(0)으로 컴파일러가 최적화를 유도했습니다.

#늦은lazy 로컬 변수 선언
로컬 변수를 서브 루틴의 머리에 모아 두지 않았습니다.  변수를 쓰지 않고 빠져나갈 경우 변수를 만드는 데 든 싸이클만 낭비한 것이 되며, 변수가 쓰인 코드 블락과 멀어 코드를 읽는데 도움이 되지 않기 때문입니다.

#상수를 모아놓은 .h 파일
공유하지 않는 상수까지 모아놓는 이유를 모르겠습니다.  이 .h 파일을 수정하면 이것을 포함한 모든 .h/.cpp 파일들을 새로 컴파일해야 하는데 말입니다.

#Unnamed scope
Unnamed scope로 지역 변수의 수명을 필요한 만큼만 두어 에러 위험을 줄였습니다.

#문자열을 받는 인수parameter
nullptr을 걸러낼 수 없는 char*보다 const char (&)[N]를, 문자열 리터럴이 메모리에 남는 const char (&)[N]보다 std::string을 선호했습니다.
char*이 쓰인 곳은 재귀 함수와 윈속 send 함수뿐입니다.
( staticLibs/Lib/Hash.h:11, Socket.h )

#STL 원소에 임의 접근random access
std::array와 std::vector는 직접 범위 검사를 하고 연산자 []로 접근했습니다.  멤버 함수 at(...)은 내부에서 std::exception 예외 처리를 하기 때문에 느리기 때문입니다.
std::unordered_set과 std::unordered_map은 멤버 함수 find(...)로 접근하되, 있는 값인지 검사할 필요가 없는 경우에만 연산자 []로 접근했습니다.  없는 값에 연산자 []로 접근하면 값을 새로 넣기 때문입니다.  멤버 함수 at(...)을 쓰지 않은 것은 전과 같습니다.

#시간 복잡도 #실제 속도
시간 복잡도가 낮다고 실제 속도가 빠르진 않습니다.  예로, 자료 구조 중간에 있는 원소를 빼내거나 없애거나 새로 넣는 연산이 잦은 경우, 배열보다 연결 리스트를 쓰곤 합니다.  배열을 쓰면 그 원소 뒤에 있는 모든 원소들을 한 칸 씩 당기거나 밀어야하는데, 연결 리스트는 아니기 때문입니다.  하지만 이는 원소의 크기가 64 바이트 이상 클 때에 한합니다.  연결 리스트가 포인터로 메모리를 간접 접근하는 비용이 작지 않아 원소의 크기가 작은 경우엔 오히려 배열이 빠릅니다.  이 경우에도 단일singly 연결 리스트는 여전히 배열보다 빠르지만 직전 원소를 따로 다루어야 해서 코드가 길어지고, 원소를 자료 구조 가장 뒤에 넣기에 부적합합니다.
( exes/Engine/main.cpp:126, 

#Aggregation 관계
함수의 시그니처를 바꾸려니 오버라이드하고 있는 순수 가상 함수의 시그니처까지 바꾸어야 하는 경우 생성자로 레퍼런스를 쥐어주어 aggregation 관계가 생겼습니다.  함수의 인수가 많지 않다면 필요할 때마다 인자로 넘기는 dependency 관계를 더 선호했습니다.  코드를 읽기 쉬웠기 때문입니다.
( dlls/Game/scene/inPlay/InPlay.h:30, Playing.h:52, 

#상속
인터페이스를 구현할 때 외엔 전혀 쓰지 않았습니다.
다음과 같은 이유 때문에 상속은 지양해야 합니다.
1. 연필에도 볼펜에도 심이 있습니다.  그래서 심을 속성으로 갖는 펜 클래스를 두고 연필 클래스와 볼펜 클래스가 펜 클래스를 상속했습니다.  시간이 지나 심이 없는 스타일러스 펜도 다루게 되었습니다.  스타일러스 펜 클래스가 필요없는 심 속성까지 가지며 펜 클래스를 상속하면, 메모리가 낭비되는 것은 물론 모르는 사이 virtual 키워드가 붙지 않은 함수를 오버라이드할 수 있습니다.
2. 연필과 볼펜은 흉기이기도 합니다.  그래서 데미지를 속성으로 갖는 흉기 클래스를 상속하려고 합니다.  일관된 결정이지만 다중 상속은 위험합니다.  색연필처럼 흉기가 될 수 없는 펜도 있으니 펜 클래스가 흉기를 상속할 수도 없습니다.
3. 오로지 코드를 일부나마 재사용하려고 상속을 썼습니다.  곧 1과 같은 문제에 직면했습니다.
4. 기존 코드를 가능한 한 바꾸지 않고 유지보수하려고 상속을 썼습니다.  1과 같은 문제가 생기는 동시에 쓸모없는 코드가 증식했습니다.

(그림)#씬 계층
클래스 ::scene::inPlay::InPlay와 ::scene::online::Online은 인터페이스 ::scene::IScene의 구체concrete 클래스이지만 사실 씬이 아닙니다.  간이 씬 매니저입니다.  굳이 씬 매니저까지 나와 처리할 필요가 없는 것들을 위임delegate한 것입니다.  이로써 코드를 읽기도 쉽고 분업하기도 쉽게 되었습니다.
또, 해제하지 않고 다음 씬에 넘기고 싶은 인스턴스를 공유하기에 쉬웠습니다.
( dlls/Game/scene/inPlay/Ready.h, Playing.h, GameOver.h의 생성자에 넘긴 sf::Drawable 레퍼런스 )

#goto
break로 둘 이상의 스코프를 빠져나가지 못하는 경우, 읽기 쉬우면서 코드 중복을 피할 수 있는 경우에 한해서만 점프 키워드 goto를 사용했습니다.
( dlls/Game/scene/MainMenu.cpp:1000, 

#예외 처리
읽기 쉽고 빠른 if 문으로 처리하고 try-catch 블록을 쓰지 않았습니다.

#로그
별도의 파일로 출력하지 않고 콘솔에 출력합니다.

#스크립트 불러오기
스크립트에서 불러오지 못한 경우를 대비해 변수에 기본값을 주었습니다.  그리고 값을 스크립트에서 불러와 타입이나 범위를 검사한 뒤에야 변수에 덮어썼습니다.  이 과정에서 실패하면 콘솔에 출력합니다.
( dlls/Game 이하 많은 클래스에 정의된 멤버 함수 loadScript(...) )
https://youtu.be/uPx0DgMIeoQ

#멤버 변수의 선언 순서 #패딩
멤버 변수의 크기가 작은 것부터 위에서 아래로 선언하여 패딩을 줄였습니다.
컴파일러가 최적화할 수 있도록 초기화 리스트상 순서 역시 선언 순서와 맞추었습니다.

#씬 전환 #씬 인스턴스 생성
각 씬의 요청에 따라 씬 매니저에서 다음 씬의 인스턴스를 만듭니다.  각 씬에서 알아서 다음 씬의 인스턴스를 만들고 그 인스턴스의 주소만 씬 매니저에 넘기면 되는 방식은 개발 중 파기되었습니다.  콘솔이나 스크립트로 특정 씬을 곧바로 열기 위해 전자의 방법은 써야 했는데, 후자의 방법까지 혼용하니 코드가 복잡했기 때문입니다.
각 방법의 장단점은 다음과 같습니다. 전자의 방법은 새로운 구체concrete 클래스가 등장할 때마다 분기문을 추가해주어야 합니다만 파기된 후자의 방법은 그렇지 않습니다. 대신 파기된 후자의 방법은 다음 씬의 .h 파일이 바뀌면 이 파일을 포함한 모든 파일을 연쇄적으로 다시 컴파일해야 하고, 후자의 방법은 씬 매니저만 새로 컴파일하면 됩니다.
( dlls/Game/scene/SceneManager.h:29와 함수 setScene(...), 

#가시성 #접근 한정자
코드를 조금이라도 더 읽기 쉽도록 클래스든 구조체든 상속이든 가시성을 명시했습니다.
인터페이스의 생성자는 protected로 가시성을 제한하여 인스턴스를 명시적으로 만들지 못하고 구체concrete 클래스에서 암시적으로만 만들 수 있도록 했습니다.

#초기화 리스트
오작동 방지 겸 생성자에서 초기화한다면 초기화 리스트로 성능을 챙기는 것이 맞지만, init(...) 등 별도의 함수로 초기화하는 경우에도 그런 지에 대해선 의문입니다.

#멤버 변수 이름
널리 쓰이는 코딩 스탠다드대로 알파벳 소문자 m을 앞에 붙였습니다.  이는 IDE에 의존하지 않고 멤버 변수를 다른 변수로부터 쉽게 구분할 수 있게 해줍니다.
Aggregation 관계에 있거나 같은 연산을 반복하지 않도록 멤버 함수의 바깥 스코프로 빼내 수명을 늘린 것에 불과한 변수엔 이름 뒤에 특수문자 _를 붙였습니다.  이런 변수는 인스턴스의 상태인 멤버 변수와 구별해야 코드를 읽을 때 방해되지 않기 때문입니다.
명사구는 후치 형용했습니다.  이름이 기억나지 않아도 인텔리센스로 쉽게 찾을 수 있었기 때문입니다.  예를 들면, mSoftDropIntervalFrameCount와 mCoolFrameCount가 아니라 mFrameCountSoftDropInterval과 mFrameCountCool을 썼습니다.

#인스턴스 카운팅
일부 클래스의 총 인스턴스 수를 제한했습니다.

#RTTI
성능에 가시적인 영향이 없는 경우에 한해서만 RTTI를 썼습니다.
( dlls/Game/scene/Playing.cpp:952, dlls/Game/scene/IScene.h의 순수 가상 함수 currentScene() )

#인터페이스
기반base 클래스, 직계존속(?)parent, grandparent 클래스, 순수 가상 함수pure virtual function만 선언된 추상 클래스라는 이명들 대신 자바의 인터페이스라는 이름을 차용했습니다.  인터페이스를 쉽게 구분하도록 클래스 이름, .h/.cpp 파일 이름 앞에 알파벳 대문자 아이I를 붙였습니다.
접근한정자로 인터페이스의 인스턴스를 함부로 만들지 못하게 했습니다.

#키워드 friend
키워드 friend가 항상 정보 은닉을 파괴하는 것은 아닙니다.
( staticLibs/Shared Headers Only/IGame.h, dlls/Game/ServiceLocatorMirror.h와 Game.cpp )

#SFINAE
컴파일해야 알려주는 static_assert보다 인텔리센스가 알려주는 SFINAE 기법이 협업에 더 도움이 될 것이라 생각했습니다.
( staticLibs/Lib/ScriptLoader.h )

#SFML
SFML은 SDL처럼 오픈 소스 멀티미디어 라이브러리입니다.  SDL이 C 언어로 작성된 반면 SFML은 C++로 작성되었습니다.  그렇기에 OOP의 좋은 예를 들여다볼 수 있고, 높은 수준에서 점차 낮은 수준으로 학습할 수 있었습니다.

#헤더 파일을 포함하는 순서
스탠다드, 제 3자, 직접 만든 라이브러리 순으로 포함하되, 순서 때문에 컴파일 에러가 발생하는 경우엔 다릅니다.
(exes/Engine:pch.h:10)

#정적static 라이브러리
아무리 .obj 파일을 재사용할 수 있다지만 아예 떼어놓는 것이 커플링을 막고 편하게 재사용하며 빌드 시간도 줄일 수 있는 좋은 방법입니다.  이미 링크되었기 때문에 바이너리 파일을 실행할 때 별도의 파일을 로드할 필요가 없다는 것, 출력 파일이 크다는 것은 고려 사항이 아니었습니다.

#.dll
Mod, 확장팩이나 심지어 다른 게임에서 재사용할 수 있는 코드는 범용성에 따라 라이브러리나 exes/Engine 프로젝트에 두고, 컨텐츠에 특화된 코드는 dlls/ 아래 프로젝트에 두었습니다.  런타임 중 .dll 파일을 해제하고 다른 .dll 파일을 로드할 수 있도록 명시적으로 링크하였습니다.
여러 프로세스에서 공유하기 위해 만든 건 아닙니다.

#루아 스크립트
로직은 빠르고 디버깅이 쉬워야 하므로 C++에서, 기획자와 아티스트가 부담없이 자주 바꿀 수 있어야 하는 데이터와 리소스는 루아 스크립트로 처리했습니다.

#콘솔
콘솔에 명령어와 함수를 매핑하여 런타임 중 다양한 시도를 해볼 수 있었습니다.  현재는 수정한 스크립트를 다시 불러오거나, 원하는 씬으로 이동하거나, GUI가 미완성이거나 바뀔 경우를 대비해 방을 생성하거나 들어가는 등의 명령어가 등록되어 있습니다.
( dlls/Game/SceneManager.cpp:19 )
명령에 따라 공유 데이터를 상호 배제해야 했습니다.

#키워드 auto
타입을 명시하기엔 너무 긴데 근처 코드에서 쉽게 유추할 수 있는 경우에만 키워드 auto를 썼습니다.  미래의 자신을 포함한 다른 사람이 코드를 읽는 데 키워드 auto가 오히려 방해가 될 수 있기 때문입니다.

#문자열 리터럴
문자열 리터럴은 char[]나 std::string으로 받았습니다.  const char*로 받은 문자열 리터럴은 메모리에 남아 보안에 해가 되기 때문입니다.

#문자열 해싱
문자열을 해싱하여 비교하는 것이 ::strcmp(...) 등으로 그대로 비교하는 것보다 유의미하게 빨랐습니다.

#전역 변수
정의되는 순서가 딱히 정해져있지 않고, 인자로 넘기지 않아 언제 어느 서브루틴에서 접근하는지 한눈에 보이지 않아 전역 변수를 소극적으로 쓰고 한 곳에 모아두었습니다.
유연하게 쓰기 위해 싱글턴 패턴 대신 서비스 로케이터 패턴을 썼습니다.
( staticLibs/Shared Headers Only/IServiceLocator.h, exes/Engine/ServiceLocator.h, dlls/Game/ServiceLocatorMirror.h )
\

라이센스
--------
+ [**zlib/png**](https://www.sfml-dev.org/license.php) for SFML
+ OFL for fonts