# -*- coding: utf-8 -*-

NORMAL版本性能较差，但支持所有题目要求的功能。
HIGH_PERFORMANCE版本的算法复杂度有本质差别，但禁用删除节点功能(这会导致已有的address和alias全部失效，给GUI测试带来困难)，至多允许放入PREALLOC个节点(我在此编译时使用PREALLOC=1M)。

# english if fucking GBK annoying you
NORMAL version has much lower performance, but supports all required functions.
HIGH_PERFORMANCE version has an essential difference in time complexity, but `DeleteVex(removeNode)` function is removed because it will invalidate all node address/alias, which is annoying GUI tester. In addition, you can put at most PREALLOC nodes into one graph, and PREALLOC is set to 1M in pre-compiled version.

To run DYNAMIC linked windows edition program, you must have gcc installed or download libstdc++ at `https://drive.recolic.net/f/32d2d22fe4/`.
