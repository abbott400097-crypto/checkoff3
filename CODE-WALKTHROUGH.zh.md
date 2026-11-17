# 先看懂这个程序，再准备讲它

这个项目的代码只做四件事：准备原始数组、编码、解码、比较还原结果。
入口在 `src/demo.c` 的 `main()`；真正的算法在 `src/rle.c`。

## 1. 先弄懂输入和输出

```c
uint8_t original[] = {7, 7, 7, 7, 7, 2, 2, 2};
```

`uint8_t` 是 8 位无符号整数类型，能存 0 到 255。在这个平台上每个
元素占一个字节。这里的 7 和 2 可以理解为两个颜色编号。

编码结果应该是：

```text
5, 7, 3, 2
```

每两个数字是一对：`5,7` 表示五个 7；`3,2` 表示三个 2。
颜色编号 0 也可以正常存储，所以程序另外传入数组长度，不靠字符串
末尾的 `\0` 判断结束。

## 2. 函数参数是什么

```c
size_t rle_encode(const uint8_t *src, size_t n,
                  uint8_t *dst, size_t capacity)
```

| 名字 | 在这里的意思 |
|---|---|
| `src` | 原始数组首元素的地址；函数读取这里的值 |
| `n` | 原始数组一共有多少个字节 |
| `dst` | 输出数组首元素的地址；函数把结果写在这里 |
| `capacity` | 输出数组最多能装多少个字节 |
| `size_t` | C 中用来表示大小或下标的一种无符号整数类型 |
| `const` | 函数不能通过这个 `src` 指针修改输入值 |

返回值是实际写入的字节数。`SIZE_MAX` 在这个程序里用作错误标记。
正常教学例子只需要记住：输入数组给它，它在输出数组里写编码结果。

## 3. 编码循环：先数一段，再写一对

下面是实际函数的核心部分：

```c
size_t out = 0;
for (size_t i = 0; i < n;) {
    size_t count = 1;
    while (count < 255 && count < n - i && src[i + count] == src[i]) {
        ++count;
    }
    if (capacity - out < 2) return SIZE_MAX;
    dst[out++] = (uint8_t)count;
    dst[out++] = src[i];
    i += count;
}
```

三个变量：

- `i`：这一段在原始数组里的起点。
- `count`：这次已经数到几个连续相同的值。
- `out`：下一次应该写到输出数组的哪个位置。

用 `{7,7,7,7,7,2,2,2}` 手动过一遍：

| 轮次 | `i` | `src[i]` | 数出来的 `count` | 写入输出 | 下一轮 `i` |
|---|---:|---:|---:|---|---:|
| 第一轮 | 0 | 7 | 5 | `5,7` | 5 |
| 第二轮 | 5 | 2 | 3 | `3,2` | 8，结束 |

`while` 的三个条件分别防止次数超过255、读取越界，以及跨进另一种颜色。
这里 `for` 的第三部分没有写 `i++`，因为每轮末尾已经用 `i += count`
跳过整段处理完的元素。

`dst[out++] = ...` 的意思是：先写到当前 `out` 对应的位置，再把 `out`
加一。连续两行分别写次数和值。

## 4. 解码：每次读两个数字

```c
for (size_t i = 0; i < n; i += 2) {
    size_t count = src[i];
    uint8_t value = src[i + 1];
    if (count == 0 || count > capacity - out) return SIZE_MAX;
    memset(dst + out, value, count);
    out += count;
}
```

每次 `i += 2`，因为一对占两个元素。`memset(dst + out, value, count)`
在输出的当前位置，写入 `count` 个相同的字节 `value`。
这里每个值本来就是一个字节，所以可以这样使用 `memset`。

程序还会拒绝奇数长度的编码：最后如果只剩一个数字，就凑不成完整一对。

## 5. 怎么证明是无损

```text
原始数组 → 编码数组 → 解码数组
    └──── 比较长度，再逐字节比较 ────┘
```

`memcmp` 比较原始数组与解码数组的内容，返回0表示比较的字节相同。
`assert` 检查条件；条件不成立时会让测试失败。输出里的 `exact=yes`
代表这次输入完整还原，不代表所有可能输入都经过穷举测试。

## 6. 这份代码可以讲的三个发现

**同样的数字总数，不同排列，结果不同。**

```text
0000000011111111 → (8,0)(8,1) → 4 bytes
0101010101010101 → 16 个长度为1的对 → 32 bytes
```

两组都有八个0、八个1。用哈希表统计“0有几个、1有几个”，无法分辨
这两组输入。实验用一个计数数组核对频率相同，没有实现完整哈希表。

**300 个相同值需要拆分。**

一个无符号字节最大是255，所以300个7写成 `(255,7)(45,7)`。
它还是同一段连续重复，只是编码格式要求拆成两对。

**什么时候能省？**

原始 `n` 个字节，编码为 `p` 对，就需要 `2p` 字节。
`2p < n` 才变小。举例：四个相同值写成一对，4变2；一个单独值写成
一对，1变2。这个结论只针对我们定义的“两字节一对”的格式。

## 7. 现场不用讲完所有代码

主讲编码与解码的思路，展示实验结果即可。数组顺序、255边界、为何
变大适合问答。测试里的异常输入和容量检查是验证代码用的，不需要
挤进5–7分钟的主讲。

常见英语短答：

- **Why not a hash table?** A value-to-total-count table loses the order of the runs.
- **What if the run is longer than 255?** We split it into multiple count-value pairs.
- **Why can the result grow?** Every pair needs a count byte, even for a single value.
- **How do you check losslessness?** We decode the result and compare it with the original byte array.

这些是理解提示。讲述时按自己的理解表达，不要声称自己做过尚未做过的测试。
