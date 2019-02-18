/*
1.先make 生成cs文件夹
  编译：javac demo.java
  运行：java demo DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL(魔方序列)
2.调用函数为Search.class中的solution方法
  输入：字符串，长度36
  输出：字符串，长度不定
*/
import cs.min2phase.Search;

public class demo {
    public static void main(String[] args) {
        
        //当前时间
	    //long startTime=System.currentTimeMillis();
        
        /*输入打乱后的魔方序列，样例：DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL
        整体输入顺序：     
              1
            5 3 2 6
              4
        每个面的输入顺序为：平面图的左上到右下依次编号
            1 2 3
            4 5 6
            7 8 9
        */
        String scrambledCube = args[0]; //读入要处理的字符串
        //调用sulution方法进行计算，第二个参数表示搜索的目标最小步数，一般情况下21可行，调大一些貌似也没有影响
        String result = new Search().solution(scrambledCube, 21, 100000000, 0, 0);
        //输出样例：R  F2 U  B  L2 D  R  L2 F  R2 L  B  D  R2 B' R2 B2 U' B2 R2 U
        System.out.println(result);

        //结束时间，计算总体运行时间
	    //long endTime=System.currentTimeMillis();
	    //float excTime=(float)(endTime-startTime)/1000;
	    //System.out.println("Time："+excTime+"s");
    }
}
