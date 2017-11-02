#import <Foundation/Foundation.h>
@interface Heap : NSObject
@property (nonatomic, strong) NSMutableArray <NSNumber *> *data;
+ (void)demo;
- (instancetype)initWithArray:(NSArray *)array;
- (NSArray *)heapSort;
- (void)push:(NSNumber *)number;
- (NSNumber *)pop;
@end

@implementation Heap
- (instancetype)init {
    self = [super init];
    if (self) {
        self.data = @[@0].mutableCopy;
    }
    return self;
}

+ (void)demo {
    NSArray *a = @[@1, @3, @2, @4];
//    NSArray *a = @[@1];
//    NSArray *a = @[@3, @5, @2, @9, @8, @4, @3, @7, @22];
    Heap *h = [[Heap alloc] initWithArray:a];
    NSLog(@"🌞👉🏻%@👈🏻🌞", h.heapSort);
    NSLog(@"🌞👉🏻%@👈🏻🌞", [h pop]);
    NSLog(@"🌞👉🏻%@👈🏻🌞", [h pop]);

}

- (instancetype)initWithArray:(NSArray *)array {
    self = [super init];
    if (self) {
        self.data = @[@0].mutableCopy;
        for (NSNumber *i in array) {
            [self push:i];
        }
    }
    return self;
}

- (NSArray *)heapSort {
    NSMutableArray *res = @[].mutableCopy;
    while (self.data.count > 1) {
        [res addObject:[self pop]];
    }
    return [NSArray arrayWithArray:res];
}

- (void)push:(NSNumber *)number {
    [self.data addObject:number];
    [self heapifyUp:self.data.count - 1];
}

- (NSNumber *)pop {
    if (self.data.count > 1) {
        [self swap:1 indexB:self.data.count - 1];
        NSNumber *p = self.data.lastObject;
        [self.data removeLastObject];
        [self heapifyDown:1];
        return p;
    }
    return nil;
}

- (NSNumber *)peek {
    if (self.data.count > 1) {
        return self.data[1];
    }
    return nil;
}

- (void)heapifyUp:(NSUInteger)index {
    while ([self parentIndex:index]) {
        if (self.data[index] < [self parent:index]) { // change here for max heap
            [self swap:index indexB:[self parentIndex:index]];
        }
        index = [self parentIndex:index];
    }
}

- (void)heapifyDown:(NSUInteger)index {
    while ([self hasLeftChild:index]) {
        NSUInteger smallerChildIndex = [self smallerChildIndex:index];
        if (self.data[smallerChildIndex] < self.data[index]) { // change here for max heap
            [self swap:smallerChildIndex indexB:index];
        }
        index = smallerChildIndex;
    }
}

- (NSInteger)smallerChildIndex:(NSUInteger)index {
    NSUInteger smallerChildIndex = -1;
    if ([self hasLeftChild:index]) {
        smallerChildIndex = [self leftChildIndex:index];
    }
    if ([self hasRightChild:index]) { // change here for max heap
        smallerChildIndex = self.data[[self rightChildIndex:index]] < self.data[[self leftChildIndex:index]] ? [self rightChildIndex:index] : [self leftChildIndex:index];
    }
    return smallerChildIndex;
}

#pragma mark - private
- (NSUInteger)parentIndex:(NSUInteger)index {
    return index / 2;
}

- (NSUInteger)leftChildIndex:(NSUInteger)index {
    return index * 2;
}

- (NSUInteger)rightChildIndex:(NSUInteger)index {
    return index * 2 + 1;
}

- (NSUInteger)hasParent:(NSUInteger)index {
    return [self parentIndex:index] > 0;
}

- (NSUInteger)hasLeftChild:(NSUInteger)index {
    return [self leftChildIndex:index] < self.data.count;
}

- (NSUInteger)hasRightChild:(NSUInteger)index {
    return [self rightChildIndex:index] < self.data.count;
}

- (NSNumber *)parent:(NSUInteger)index {
    return self.data[[self parentIndex:index]];
}

- (NSNumber *)leftChild:(NSUInteger)index {
    return self.data[[self leftChildIndex:index]];
}

- (NSNumber *)rightChild:(NSUInteger)index {
    return self.data[[self rightChildIndex:index]];
}

- (void)swap:(NSUInteger)indexA indexB:(NSUInteger)indexB {
    NSNumber *temp = self.data[indexA];
    self.data[indexA] = self.data[indexB];
    self.data[indexB] = temp;
}
@end
