# 5.2

## (3)

- `copy2_highio.c`よりも`copy2_lowio.c`の方が実行速度が遅い。
- バッファのサイズが異なり、後者の方がシステムコールを呼ぶ回数が多くなるため。

## (4)/(5)

- 一回でコピーするサイズを大きくすればするほど両者の差は縮まる。
- システムコールを呼ぶ回数が小さくなるため。

## 5.3

- `5.2`よりも高速にコピーできる。
- バッファのサイズが大きくなり、システムコールを呼ぶ回数が少なくなるため。

