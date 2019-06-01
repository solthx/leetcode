"""
	题目描述：
		将非负整数转换为其对应的英文表示。可以保证给定输入小于 231 - 1 。

		示例 1:

		输入: 123
		输出: "One Hundred Twenty Three"
		示例 2:

		输入: 12345
		输出: "Twelve Thousand Three Hundred Forty Five"
		示例 3:

		输入: 1234567
		输出: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
		示例 4:

		输入: 1234567891
		输出: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

		
	题目分析：
		递归，分区间讨论，利用递归更方便
"""


class Solution:
    def numberToWords(self, num: int) -> str:
        if ( num==0 ):
            return "Zero"
        gewei = {
            1 : 'One',
            2 : 'Two',
            3 : 'Three',
            4 : 'Four',
            5 : 'Five',
            6 : 'Six',
            7 : 'Seven',
            8 : 'Eight',
            9 : 'Nine',
        }
        shiwei = {
            2: 'Twenty',
            3: 'Thirty',
            4: 'Forty',
            5: 'Fifty',
            6: 'Sixty',
            7: 'Seventy',
            8: 'Eighty',
            9: 'Ninety',
        }
        shiji = {
            10: 'Ten',
            11: 'Eleven',
            12: 'Twelve',
            13: 'Thirteen',
            14: 'Fourteen',
            15: 'Fifteen',
            16: 'Sixteen',
            17: 'Seventeen',
            18: 'Eighteen',
            19: 'Nineteen'
        }
        other = {
            100:'Hundred',
            1000:'Thousand',
            1000000:'Million',
            1000000000:'Billion'
        }
        res_list = []
        # 大于十亿
        if ( num>=1000000000 ):
            res1 = gewei[num//1000000000] + " Billion"
            res_list.append(res1)
            num = num % 1000000000
        
        # 大于百万
        if ( num>=1000000 ):
            res2 = self.numberToWords(num//1000000) + " Million"
            res_list.append(res2)
            num = num % 1000000
            
        # 大于千
        if ( num>=1000 ):
            res3 = self.numberToWords(num//1000) + " Thousand"
            res_list.append(res3)
            num = num % 1000
        
        # 大于百
        if ( num>=100 ):
            res4 = self.numberToWords(num//100) + " Hundred"
            res_list.append(res4)
            num = num %100
        
        # 大于20
        if ( num>=20 ):
            res5 = shiwei[num//10]
            res_list.append(res5)
            num = num % 10
        
        # 大于10
        if ( num>=10 ):
            res6 = shiji[num]
            res_list.append(res6)
        elif (num>0):
            # 小于10
            res6 = gewei[num]
            res_list.append(res6)
        res = ""
        for e in res_list:
            if ( e is not "" ):
                res = res + " "+e
        return res.strip()
        