#Robotopia  

##6주차 업데이트 노트  
week6 폴더안에 바로 실행 가능한 Release 파일이 있습니다  

###조작###
- WASD - 이동  
  * 포탈(블록이 4등분난 모양) 위에서 W키를 누르면 다음 층으로 이동 가능합니다. 
- SPACE - 점프(S + 점프 -> 특정 블록(floor)위에서는 다운 점프 가능) 
  * SPACE키를 꾹 누르면 높이, 살짝 누르면 낮게 뜁니다
- 1,2,3 - 기어 변환. 3번 기어 상태일 때는 날 수 있음. 마우스 휠로도 가능.
 * 1번 기어에서 마우스 왼쪽 클릭 -> 근접 공격
 * 2번 기어에서 마우스 왼쪽 클릭 -> 원거리 공격(마우스 방향)

###플레이어
- 점프 제어 기능 추가. Space bar를 누르는 정도에 따라 점프 정도가 달라짐.
- 근접 공격 추가.(1번 기어 상태에서 왼쪽 클릭 - 무빙샷 됨)
- 원거리 공격 추가. (2번 기어 상태에서 왼쪽 클릭 - 무빙샷 안됨)
- 넉백 추가. (몹한테 맞으면 튕겨나감.)
- Hp, Steam 감소 추가. Hp가 0이 되면 Assembly 화면으로 돌아감.(재시작은 아직 버그 있음.)
- Assembly씬에서 착용한 아이템 기반으로 스탯 생성.

###몬스터
- 시체 추가(죽으면 시체 나옴)

###맵
- 레이저 타일 추가. 주기적으로 꺼졌다 켜졌다 하면서 플레이어 넉백 및 데미지..
- 전선 타일 추가. 전기 흐르는 곳에 닿으면 플레이어 넉백 및 데미지.

###로봇 조립(Assembly 씬)
- 부품 조립시 부품의 스탯이 실제 플레이어 스탯에 반영됨.
- 부품 업그레이드 기능 추가.
- 반영된 실제 플레이어 스탯 표시 기능 추가
- 아이템 바꿨을 때 스탯 변동치 표시 기능 추가
- 어셈블리 씬에서 아이템 여러 개 선택되던 버그 수정
