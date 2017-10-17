import Foundation

class GraphNode:Hash, CustomStringConvertible {
    var val:Int
    var neighbors:[GraphNode] = []
    
    init(val:Int) {
        self.val = val
    }
    
    var description: String { // CustomStringConvertible
        return "val=\(self.val),neighbors=\(self.neighbors)"
    }
    
    static func toGraph(dataList:[Int]) -> GraphNode {
        
        func formatGraphList(dataList:[Int]) -> [[Int]]{
            var res:[[Int]] = []
            var new:[Int] = []
            for i in dataList {
                if i != -1 {
                    new.append(i)
                }
                else {
                    res.append(new)
                    new = []
                }
            }
            res.append(new)
            return res
        }
        
        func getNode(num:Int, nodeDict:inout [Int: GraphNode]) -> GraphNode {
            if nodeDict.keys.contains(num) == false {
                nodeDict[num] = GraphNode(val: num)
            }
            return nodeDict[num]!
        }
        
        var graphList:[[Int]] = formatGraphList(dataList: dataList)
        let root = GraphNode(val: graphList[0][0])
        var nodeDict:[Int: GraphNode] = [graphList[0][0]: root]
        for each in graphList {
            if each.count == 0 {
                continue
            }
            
            if each.count == 1 {
                let node = getNode(num: each[0], nodeDict: &nodeDict)
                node.neighbors.append(node)
            } else {
                let node = getNode(num: each[0], nodeDict: &nodeDict)
                for eachNum in each[1..<each.count] {
                    let eachNode = getNode(num: eachNum, nodeDict: &nodeDict)
                    node.neighbors.append(eachNode)
                }
            }
            
        }
        return root
    }
    
    static func toList(root:GraphNode) -> [Int] {
        
        func dfs2(root:GraphNode?, map:inout [GraphNode: Int]) {
            guard let root = root else {return}
            map[root] = 1
            for i in root.neighbors {
                if map.keys.contains(i) == false {
                    dfs2(root: i, map: &map)
                }
            }
        }
        
        var map:[GraphNode: Int] = [:]
        dfs2(root: root, map: &map)
        var res:[[Int]] = []
        var chosed:[Int] = []
        for node in map.keys {
            chosed.append(node.val)
            for i in node.neighbors {
                chosed.append(i.val)
            }
            chosed.append(-1)
            res.append(chosed)
            chosed = []
        }
        
        let sorted = res.sort { left, right in
            left[0] < right[0]
        }
        
        //    res.sort { $0[0] < $1[0] }
        
        var resList:[Int] = []
        for eachList in res {
            for i in eachList {
                resList.append(i)
            }
        }
        //    while let last = resList.last as? String {
        //        if last == "#" {
        //            resList.removeLast()
        //        }else {
        //            break
        //        }
        //    }
        return resList
    }
    
    static func demo() {
        let a:[Int] = [1,2,3,-1,3,2] // -1 as "#" for this case
        let root = toGraph(dataList: a)
        let res = toList(root: root)
        print(res)
    }
}




