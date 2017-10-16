import Foundation

class Tree {
    static func testTree(){
        var nodeList:[Any] = [1,2,3,"#",4,"#","#",5]
        let root = TreeNode.toTree(nodeList: &nodeList)
        let resutlList = TreeNode.toTreeList(root: root)
        print(resutlList)
    }
}
