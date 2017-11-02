#import <Foundation/Foundation.h>
#define NSUINT_BIT (CHAR_BIT * sizeof(NSUInteger))
#define NSUINTROTATE(val, howmuch) ((((NSUInteger)val) << howmuch) | (((NSUInteger)val) >> (NSUINT_BIT - howmuch)))
@interface GraphNode : NSObject <NSCopying>

@property (nonatomic, assign) id val;
@property (nonatomic, strong) NSMutableArray <GraphNode *>*neighbors;

- (instancetype)initWith:(id)val;

@end

@implementation GraphNode

- (NSUInteger)hash {
    NSUInteger a = [NSString stringWithFormat:@"%p", self].hash ;
//    NSLog(@"🌞👉🏻%lu👈🏻🌞", (unsigned long)a);
//    NSUInteger a = NSUINTROTATE([self.val hash], NSUINT_BIT / 2) ^ [self.neighbors hash];
//    NSUInteger a =  [self.val hash] ^ self.neighbors.hash;
    return a;
}

- (BOOL)isEqual:(GraphNode *)object {
    if (![object isKindOfClass:self.class]) {
        return NO;
    }
    return object.val == self.val;
//    return object.hash == self.hash;
}

- (id)copyWithZone:(NSZone *)zone {
    GraphNode *objectCopy = [[GraphNode allocWithZone:zone] init];
    // to do: recursively copy every Node
    objectCopy.val = self.val;
    objectCopy.neighbors = self.neighbors.copy;
    return objectCopy;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"{val=%@,neighbors=%@}", self.val, self.neighbors];
}

- (instancetype)initWith:(id)val {
    self = [super init];
    if (self) {
        _val = val;
        _neighbors = [NSMutableArray array];
    }
    return self;
}

+ (void)demo {
    
    NSArray *a = @[@1, @2, @3, @"#", @3, @2];
    GraphNode *root = [self toGraph:a];
    NSArray *res = [self toList:root];
    NSLog(@"🌞👉🏻%@👈🏻🌞", res);
}



+ (GraphNode *)toGraph:(NSArray *)dataList {
    
    NSMutableArray<NSMutableArray <NSNumber *>*> *graphList = [self formatGraphList:dataList].mutableCopy;
    GraphNode *root = [[GraphNode alloc] initWith:graphList[0][0]];
    NSMutableDictionary *nodeDict = [NSMutableDictionary dictionaryWithDictionary:@{graphList[0][0]: root}];
    for (NSMutableArray *each in graphList) {
        if (each.count == 0) {
            continue;
        }
        
        if (each.count == 1) {
            GraphNode *node = [self getNode:each[0] nodeDict:nodeDict];
            [node.neighbors addObject:node];
        }else {
            GraphNode *node = [self getNode:each[0] nodeDict:nodeDict];
            for (int i = 1; i < each.count; i++) {
                GraphNode *eachNode = [self getNode:each[i] nodeDict:nodeDict];
                [node.neighbors addObject:eachNode];
            }
        }
    }

    return root;
}

+ (NSArray *)formatGraphList:(NSArray *)dataList {
    NSMutableArray <NSMutableArray *> *res = @[].mutableCopy;
    NSMutableArray *new = @[].mutableCopy;
    for (id number in dataList) {
        if (![number isKindOfClass:NSString.class]) {
            [new addObject:number];
        }else {
            [res addObject:new];
            new = @[].mutableCopy;
        }
    }
    [res addObject:new];
    return [NSArray arrayWithArray:res];
}

+ (GraphNode *)getNode:(NSNumber *)number nodeDict:(NSMutableDictionary *)nodeDict {
    if ([nodeDict.allKeys containsObject:number] == NO) {
        nodeDict[number] = [[GraphNode alloc] initWith:number];
    }
    return nodeDict[number];
}

+ (NSArray *)toList:(GraphNode *)root {
    NSMutableDictionary *map = [NSMutableDictionary dictionary];
    [self DFS:root map:map];
    NSMutableArray <NSMutableArray *> *res = @[].mutableCopy;
    NSMutableArray *chosed = @[].mutableCopy;
    for (GraphNode *node in map.allKeys) {
        [chosed addObject:node.val];
        for (GraphNode *i in node.neighbors) {
            [chosed addObject:i.val];
        }
        [chosed addObject:@"#"];
        [res addObject:chosed.copy];
        chosed = @[].mutableCopy;
    }
//    sort(res);
    [res sortUsingComparator:^NSComparisonResult(NSArray *obj1, NSArray *obj2) {
       return obj1[0] > obj2[0];
    }];
    
    NSMutableArray *resList = @[].mutableCopy;
    for (NSArray *eachList in res) {
        for (NSNumber *i in eachList) {
            [resList addObject:i];
        }
    }
    
    while ([resList.lastObject isKindOfClass:NSString.class] && [resList.lastObject isEqualToString:@"#"]) {
        [resList removeLastObject];
    }
    return [NSArray arrayWithArray:resList];
}


+ (void)DFS:(GraphNode *)root map:(NSMutableDictionary *)map {
    if (!root || !map) {
        return;
    }
    NSLog(@"🌞👉🏻%lu👈🏻🌞", (unsigned long)root.hash);
    map[root] = @1;
    for (GraphNode *node in root.neighbors) {
        if (![map[node] isEqual: @1]) {
            [self DFS:node map:map];
        }
    }
}
@end

                               
