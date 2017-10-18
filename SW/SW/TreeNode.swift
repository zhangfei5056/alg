import Foundation

class TreeNode:Hashable, CustomStringConvertible {
    var val:Any
    var left:TreeNode?
    var right:TreeNode?
    
    init(_ val:Any) {
        self.val = val
    }

    var description: String { // CustomStringConvertible
        return "\(self.val)"
    }
    
    var hashValue: Int {
        let bits = Unmanaged<AnyObject>.passUnretained(self as AnyObject)
        let ptr = bits.toOpaque()
        return ptr.hashValue
    }
    
    static func ==(lhs: TreeNode, rhs: TreeNode) -> Bool {
        return lhs.hashValue == rhs.hashValue
    }



    static func toTreeList(root:TreeNode?) -> [Any] {
        var q:[TreeNode?] = [root]
        var res:[Any] = []
        while q.isEmpty == false {
            let node = q.removeFirst()
            if node == nil {
                res.append("#")
            }else {
                res.append(node!.val)
                q.append(node!.left)
                q.append(node!.right)
            }
        }
        
        while let last = res.last as? String {
            if last == "#" {
                res.removeLast()
            }
        }
        return res
    }

    static func toTree(nodeList:inout [Any]?) -> TreeNode? {
        guard var nodeList = nodeList,  nodeList.count != 0 else {
            return nil
        }
        
        if nodeList.count % 2 == 0 {
            nodeList.append("#")
        }
        
        let root = TreeNode(nodeList[0])
        var queue:[TreeNode] = [root]
        var index = 1
        while index < nodeList.count {
            let parent = queue.removeFirst()
            
            if (nodeList[index] is String) == false {
                let node = TreeNode(nodeList[index])
                parent.left = node
                queue.append(node)
            }
            index += 1
            
            if (nodeList[index] is String) == false {
                let node = TreeNode(nodeList[index])
                parent.right = node
                queue.append(node)
            }
            index += 1
        }
        return root
    }
    
    static func preOrder(root:TreeNode?) {
//        guard root != nil else {
//            return
//        }
        guard let root = root else {return}
        print(root.val)
        preOrder(root: root.left)
        preOrder(root: root.right)
        
    }
    
    static func demo(){
        var nodeList:[Any]? = [1,2,3,"#",4,"#","#",5]
        let root:TreeNode? = TreeNode.toTree(nodeList: &nodeList)
        let resutlList = TreeNode.toTreeList(root: root)
        print(resutlList)
        
        TreeNode.preOrder(root: root)
    }
}






//var a:[Any] = [1, 2, 3, "#", "#", 4]
////var a:[Any] = [1, 2, 3, 4]
//print(a)
//
////for i in a {
////    guard i != nil else {
////        print("nil")
////        continue
////    }
////    print(i!)
////
////}
//
//
//let root = toTree(nodeList: &a)
//preOrder(root: root)
//let res:[Any] = toTreeList(root: root)
//print(res)




