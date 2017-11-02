
class ListNode:Hashable, CustomStringConvertible {
    var val:Int
    var next:ListNode?
    
    var description: String { // CustomStringConvertible
        return String(describing: self.val)
    }
    
    var hashValue: Int {
        let bits = Unmanaged<AnyObject>.passUnretained(self as AnyObject)
        let ptr = bits.toOpaque()
        return ptr.hashValue
    }
    
    static func ==(lhs: ListNode, rhs: ListNode) -> Bool {
        return lhs.val == rhs.val
    }

    init(_ data:Int) {
        self.val = data
    }
    
    static func toLinkedList(array:[Int]) -> ListNode? {
        guard array.count != 0 else {
            return nil
        }
        let dummy = ListNode(-1)
        var p_dummy = dummy
        for i in 0..<array.count {
            let node = ListNode(array[i])
            p_dummy.next = node
            p_dummy = p_dummy.next!
        }
        return dummy.next
    }
    
    static func toLinkedListTra(head:ListNode?) -> String {
        var res = ""
        var p_head = head
        while let node = p_head {
            res += "\(node.val)->"
            p_head = p_head?.next
        }
        return res+"null"
    }
    
    static func toLinkedList(strOrArray:AnyObject) -> ListNode? {
    
        if let str = strOrArray as? String {
            let ary:[Int] = formatStr2Array(traStr: str)
            return toLinkedList(array: ary)
        }
        if let ary = strOrArray as? [Int] {
            return toLinkedList(array: ary)
        }
        return nil
    }
    
    static func formatStr2Array(traStr:String) -> [Int] {
        var a = traStr.components(separatedBy: "->")
        a.removeLast()
        return a.map{Int($0)!}
    }
    
    
    static func toList(head:ListNode?) -> [Int] {
        if head == nil {
            return []
        }
        var res = [Int]()
        var p_head = head
        while p_head != nil {
            res.append(p_head!.val)
            p_head = p_head!.next
        }
        return res
    }
    
    static func demo() {
        let a = [1,2,3,4,5]
        
        let head = toLinkedList(array: a)
        
        print(toLinkedListTra(head: head))
        print(toList(head: head))
        print(toLinkedListTra(head: head))
        
        
        let head2 = toLinkedList(strOrArray: "1->3->null" as AnyObject)
        print(toList(head: head2))
        print(toLinkedListTra(head: head2))
        
    }
}





