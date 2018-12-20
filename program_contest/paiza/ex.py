def search(array, w, x):  #この関数で下にあるブロックの高さを求める
  a = [0] #幅それぞれの深さ(全部0の時のためとりあえず0いれとく)
  for i in range(x, x+w): #ブロック左から右
    for j in range(len(array)): #フィールドの高さ
      if array[j][i] != 0:   #もしブロックがすでにあればその高さをaに追加
        a.append(j)
        break
  if len(a) != 1: #リストの大きさが1でなければさっきの0削除
    del a[0]
  return min(a) #aの最小値 = すでにあるブロックの最も高いやつの高さを返す

def fill(array, h, w, x, b):  #この関数でブロックの存在を確立
  for i in range(b-h, b):   #bは底, 底から高さを引いたところから底まで
    for j in range(x, x+w): #ブロック左から右
      array[i][j] = 1 #ブロックがあるところは1へ

H, W, N = map(int, input().split()) #H, W, Nの入力
h, w, x = [[0 for i in range(N)] for j in range(3)] #h, w, xの空リスト生成
for i in range(N): #h, w, xの入力
  h[i], w[i], x[i] = map(int, input().split())

S = [[0 for i in range(W)] for j in range(H)] #フィールド生成
for i in range(N):
  fill(S, h[i], w[i], x[i], search(S, w[i], x[i]))  #埋める関数


for i in range(H):
  for j in range(W):
    if S[i][j] == 0: #0ならば.を
      print(".", end = "")
    else: #そうでなければ#を
      print("#", end = "")
  print()