package main

import "fmt"

// 比较接口
type Comparer interface {
    Compare(lhs interface{}, rhs interface{}) int
}

type IntComparer struct {}

func (comparer *IntComparer) Compare(lhs interface{}, rhs interface{}) int {
    lhsVal, lhsOk := lhs.(int)
    rhsVal, rhsOk := rhs.(int)

    if !lhsOk || !rhsOk {
        panic("parameter is not int")
    }

    if lhsVal < rhsVal {
        return -1
    }

    if lhsVal > rhsVal {
        return 1
    }

    return 0
}

// 置换接口
type Swapper interface {
    Swap(data []interface{}, i int, j int)
}

type IntSwapper struct {}

func (swapper *IntSwapper) Swap(data []interface{}, i int, j int) {
    tmp := data[i]
    data[i] = data[j]
    data[j] = tmp
}

// 排序接口
type Sorter interface {
    Sort(data []interface{}, comparer Comparer, swapper Swapper)
}

// 冒泡排序
type BubbleSorter struct {}

func (sorter *BubbleSorter) Sort(data []interface{}, comparer Comparer, swapper Swapper) {
    // 基本思路 : 每个波次，将最大值推到末尾

    // 第1波比较 0&1, 1&2, ..., (n-2)&(n-1)
    // 第2波比较 0&1, 1&2, ..., (n-3)&(n-2)
    // ...
    // 第k波比较 0&1, 1&2, ..., (n-k-1)&(n-k)
    // ...
    // 第n-1波比较 0&1

    n := len(data)

    for k := 1; k < n; k++ {
        for i := 0; i < n - k; i++ {
            if comparer.Compare(data[i], data[i + 1]) > 0 {
                swapper.Swap(data, i , i + 1)
            }
        }
    }
}

// 插入排序
type InsertSorter struct{}

func (sorter *InsertSorter) Sort(data []interface{}, comparer Comparer, swapper Swapper) {
    // 基本思路 : 每次将一个元素，插入到已排序的数组中

    // 第1次，将 d[1] 插入到 d[0]~d[1]
    // 第2次，将 d[2] 插入到 d[0]~d[2]
    // ...
    // 第k次，将 d[k] 插入到 d[0]~d[k]
    // // 比较 d[k] & d[k-1]
    // // 比较 d[k-1] & d[k-2]
    // // ...
    // // 比较 d[1] & d[0]
    // ...
    // 第n-1次，将 d[n-1] 插入到 d[0]~d[n-1]

    n := len(data)

    for k := 1; k < n; k++ {
        for i := k; i >= 1; i-- {
            if comparer.Compare(data[i], data[i - 1]) >= 0 {
                break
            } else {
                swapper.Swap(data, i, i - 1)
            }
        }
    }
}

// 快速排序
type QuickSorter struct {}

func (sorter *QuickSorter) Sort(data []interface{}, comparer Comparer, swapper Swapper) {
    if n := len(data); n > 1 {
        sorter.work(data, 0, n - 1, comparer, swapper)
    }
}

func (sorter *QuickSorter) work(data []interface{}, idxBegin int, idxEnd int, comparer Comparer, swapper Swapper) {
    if idxBegin >= idxEnd {
        return
    }

    // 基本思路 : 选一个基准元素，处理后，使得左边都比它小，右边都比它大，再对左右分而治之

    base := data[idxBegin]
    i := idxBegin
    j := idxEnd

    for {
        if i >= j {
            break
        }

        // 从右往左，找第一个比base小的
        for {
            if i >= j || comparer.Compare(data[j], base) < 0 {
                break
            }
            j--
        }

        // 找到这样的j，就赋值给i
        if i < j {
            data[i] = data[j]
        }

        // 从左往右，找第一个比base大的
        for {
            if i >= j || comparer.Compare(data[i], base) > 0 {
                break
            }
            i++
        }

        // 找到这样的i，就赋值给j
        if i < j {
            data[j] = data[i]
        }
    }

    data[i] = base

    if idxBegin + 1 < i {
        sorter.work(data, idxBegin, i - 1, comparer, swapper)
    }

    if i + 1 < idxEnd {
        sorter.work(data, i + 1, idxEnd, comparer, swapper)
    }
}

// 堆排序
type HeapSorter struct {}

func (sorter *HeapSorter) Sort(data []interface{}, comparer Comparer, swapper Swapper) {
    n := len(data)

    // 初始化最大堆 : 从最后一个【非叶子节点】开始，每次调整的范围是 以该节点为根的堆（包含左右子树）
    for k := n / 2 - 1; k >= 0; k-- {
        sorter.adjustSubHeap(data, k, n, comparer, swapper)
    }

    // 堆顶是最大值，与末尾元素交换
    // 再调整 以起始元素为根 排除末尾元素 的 堆（目的是为了让这个新的起始元素下沉）
    for k := n - 1; k > 0; k-- {
        swapper.Swap(data, 0, k)
        sorter.adjustSubHeap(data, 0, k, comparer, swapper)
    }
}

func (sorter *HeapSorter) adjustSubHeap(data []interface{}, idxRoot int, idxUpper int, comparer Comparer, swapper Swapper) {
    // idxRoot  : 根节点的下标
    // idxUpper : 下标上界（取不到）

    // 调整子堆的基本思路 :
    // 1. 若 当前节点 < 左右子节点的较大值，则 交换 当前节点 与 较大的那个子节点
    // 2. 若【1】不满足，则终止
    // 3. 走到 较大的那个子节点 上，继续【1】。直至走到叶子节点

    cur := idxRoot

    for {
        j := cur * 2 + 1

        if j >= idxUpper {
            break
        }

        if j + 1 < idxUpper && comparer.Compare(data[j], data[j + 1]) < 0 {
            j++
        }

        if comparer.Compare(data[cur], data[j]) < 0 {
            swapper.Swap(data, cur, j)
            cur = j
        } else {
            break
        }
    }
}

// 归并排序
type MergeSorter struct {}

func (sorter *MergeSorter) Sort(data []interface{}, comparer Comparer, swapper Swapper) {
    // 基本思路 : 不断将小的有序子序列合并，逐步扩大为整体

    // 快速排序 : 自顶而下（分而治之）
    // 归并排序 : 自底而上（逐步归拢）

    /*
    Eg : n = 8

    第一波、步长 = 1
    d[0:0] d[1:1] => d[0:1]
    d[2:2] d[3:3] => d[2:3]
    d[4:4] d[5:5] => d[4:5]
    d[6:6] d[7:7] => d[6:7]

    第二波、步长 = 2
    d[0:1] d[2:3] => d[0:3]
    d[4:5] d[6:7] => d[4:7]

    第三波、步长 = 4
    d[0:3] d[4:7] => d[0:7]
    */

    n := len(data)
    tempArray := make([]interface{}, n, n)

    for step := 1; step < n; step = step * 2 {
        sorter.work(data, tempArray, step, comparer, swapper)
        step = step * 2
        sorter.work(tempArray, data, step, comparer, swapper)
    }
}

func (sorter *MergeSorter) merge(dataFrom []interface{}, dataTo []interface{}, l int, m int, r int, comparer Comparer, swapper Swapper) {
    // 将两个排序的 dataFrom[l:m] dataFrom[m+1:r] 合并为 dataTo[l:r]
    c := l
    p1 := l
    p2 := m + 1

    for {
        if p1 > m || p2 > r {
            break
        }

        if comparer.Compare(dataFrom[p1], dataFrom[p2]) <= 0 {
            dataTo[c] = dataFrom[p1]
            p1++
        } else {
            dataTo[c] = dataFrom[p2]
            p2++
        }

        c++
    }

    for {
        if p1 > m {
            break
        }

        dataTo[c] = dataFrom[p1]
        p1++
        c++
    }

    for {
        if p2 > r {
            break
        }

        dataTo[c] = dataFrom[p2]
        p2++
        c++
    }
}

func (sorter *MergeSorter) work(dataFrom []interface{}, dataTo []interface{}, step int, comparer Comparer, swapper Swapper) {
    // 将 dataFrom 按步长step 归并排序

    /*
    d[0:s-1]   & d[s:2s-1]  => d[0:2s-1]
    d[2s:3s-1] & d[3s:4s-1] => d[2s:4s-1]
    */

    n := len(dataFrom)
    delta := step * 2
    i := 0

    for ; i + delta < n; i += delta {
        sorter.merge(dataFrom, dataTo, i, i + step - 1, i + delta - 1, comparer, swapper)
    }

    if i + step < n {
        sorter.merge(dataFrom, dataTo, i, i + step - 1, n - 1, comparer, swapper)
    } else {
        for ; i < n; i++ {
            dataTo[i] = dataFrom[i]
        }
    }
}


func main() {
    dataRaw := []int{15, 2, 14, 13, 5, 6, 0, 3, 1, 16, 10, 17, 4, 11, 18, 7, 8, 12, 9, 19}
    comparer := new(IntComparer)
    swapper := new(IntSwapper)
    sorter := new(MergeSorter)

    var data []interface{}

    for _, item := range dataRaw {
        data = append(data, item)
    }

    fmt.Println("before sort")
    fmt.Println(fmt.Sprintf("%v", data))

    sorter.Sort(data, comparer, swapper)

    fmt.Println("after sort")
    fmt.Println(fmt.Sprintf("%v", data))
}