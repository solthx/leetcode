## Best Time to Buy and Sell Stock IV   

    这个方法是从网上看到的。
    
    local[i][j]保存了前i天中最多交易j次后，并且最后一次操作是卖出，的最大值，这个是局部最大值。
    
    global[i][j]保存了前i天中最多交易j次后的最大值，这个是全局最大值，global[i][j]>=local[i][j]

### 递推：
diff_i = prices[i] - prices[i-1] 代表了前一次买，这一次卖

需要注意的是 diff_{i-1} + diff_i = prices[i]-prices[i-2] 也就是前一天什么都不做，前一天的前一天买的，今天卖的。

因此这个diff是可以传递。

下面来推递推公式，一天有三种情况：

    情况一： 当天买当天卖，0收益，就不考虑了。
    
    情况二： 前一天买的，今天卖的。 即:
    
	local[i][j] = (前一天买)( global[i-1][j-1] - prices[i-1] ) + (今天卖) prices[i] 

    情况三：前面某天买，今天卖的。即：

	local[i][j] = (之前某天买，减去的prices[i-1]可以传递抵消)(local[i-1][j]-prices[i-1]) + (今天卖) prices[i] 
    
因此可以总结为：

	local[i][j] = max(local[i-1][j],global[i-1][j-1])+diff

### *而global的很好想，就不解释了，递推为* ：
global[i][j] = max(local[i][j],global[i-1][j])