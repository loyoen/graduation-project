<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@page import="java.net.URLDecoder"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    
    <title>starting page</title>
  	 <style type="text/css">
        #searchcontrol .gsc-control
        {
            width: 100%;
        }
        #searchcontrol .gsc-result-cnblogs .gs-title
        {
            color:Red;
        }
    </style>
    <script src="https://www.google.com/jsapi?key=ABQIAAAAWUT8aaIj9mtqQa087LjVOhTPB5B7LRDljl2Cr4-JwBNft1mFrRRmR1RoYEUCZCj0dtS2gIc8Al4-VA"
        type="text/javascript" charset="utf-8"></script>      
    <script language="Javascript" type="text/javascript">
        google.load("search", "1");
 
        function OnLoad() {
        	var keyword = document.form1.user.value; 
        	//keyword=decodeURI(keyword);
  			//alert(keyword); 
        	//var key = <%=request.getParameter("key")%>
        	
            //搜索设置
            var options = new google.search.SearcherOptions();
            //当搜索结果为空时显示内容
            options.setNoResultsString('查询结果为空！');
 
            //搜索控件实例化
            var searchControl = new google.search.SearchControl();
            //每次显示8个搜索结果（取值范围：1-8）
            searchControl.setResultSetSize(8);
            //网页搜索 全部网页搜索
            var siteCnblogs = new google.search.WebSearch();
            //博客搜索  只搜索博客   
            //var siteCnblogs = new google.search.BlogSearch();
            //标头
            siteCnblogs.setUserDefinedLabel("博客搜索");
            //样式后缀名
//          siteCnblogs.setUserDefinedClassSuffix("cnblogs");
            //站点限制
            siteCnblogs.setSiteRestriction("www.cnblogs.com");
            searchControl.addSearcher(siteCnblogs, options);
 
            //局部搜索
            var siteZjfree = new google.search.WebSearch(); //只有改成WebSearch时才能正常显示url，否则就是undefined,不知为何....
            siteZjfree.setUserDefinedLabel("自由自在");
            siteZjfree.setSiteRestriction("http://loyoen1990.blog.163.com");//不能搜索转载的文章？？？？fuck
            searchControl.addSearcher(siteZjfree, options);
 
            //全网搜索
            searchControl.addSearcher(new google.search.WebSearch(), options);
 
            //添加博客搜索
//          searchControl.addSearcher(new google.search.BlogSearch(), options);
 
            //添加视频搜索
//            searchControl.addSearcher(new google.search.VideoSearch(), options);
 
            //添加新闻搜索
//            searchControl.addSearcher(new google.search.NewsSearch(), options);
 
            //添加图片搜索
//            searchControl.addSearcher(new google.search.ImageSearch(), options);
 
            //添加本地地图搜索
//            var localSearch = new google.search.LocalSearch();
            //地图中心标记 测试时可使用“大雁塔”
//            localSearch.setCenterPoint("西安,钟楼");
//            searchControl.addSearcher(localSearch, options);
            
           
            //绘制搜索
            var drawOptions = new google.search.DrawOptions();
            drawOptions.setDrawMode(google.search.SearchControl.DRAW_MODE_TABBED);
            searchControl.draw(document.getElementById("searchcontrol"), drawOptions);
             
            
            //执行搜索查询
           searchControl.setSearchCompleteCallback(this,searchComplete);
           searchControl.execute(keyword);
            
        }

        
        function searchComplete(searchControl,searcher){
        
        	 var keyword = document.form1.user.value; 
             var result = ""; //定义js变量 
             var result1 = "";
             //alert(result);
             
             var num = 8;
             if(searcher.results.length<=8)
                num = searcher.results.length;
             result += num;  //顶点数
             result += "\n";
             result += "10"; //边权重
             result += "\n";
             result += keyword; //关键词
             result += "\n";
             for(var i=0;i<searcher.results.length;i++){
                var ans = searcher.results[i];
                
                result += ans.titleNoFormatting;
                result += "\n";
                result += ans.content;
                result += "\n";
                result += ans.url;  // 不知什么原因此项为空 alert时为undefined
                result += "\n";
               // alert(result);         
            }
            if(num>4)
            {
                result1 += "4";  //顶点数
             	result1 += "\n";
            	result1 += "20"; //边权重
             	result1 += "\n";
             	result1 += keyword; //关键词
             	result1 += "\n";
                for(var j=0;j<4;j++){
                    var ans1 = searcher.results[j];
                
                    result1 += ans1.titleNoFormatting;
	                result1 += "\n";
	                result1 += ans1.content;
	                result1 += "\n";
	                result1 += ans1.url;  // 不知什么原因此项为空 alert时为undefined
	                result1 += "\n";
	              //  alert(result1);  
                } 
            }
             
       		 document.form2.test2.value = result + result1;
      		 //将js变量的值放到form中的一个隐藏域中 
      		 var formObj = document.getElementById('loyoen');
      		 formObj.submit();
        }
        
        //框架加载完成后调用
        google.setOnLoadCallback(OnLoad);
         
        
        // GetLine();
        
    </script>
  	
  
   

	
	
	
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

   </head>

  <body>
  	<div id="searchcontrol">
        加载中...
       <%String s=request.getParameter("key");%>
       <%=s%>
    </div>  
    <form name="form1">
	    <input type= "hidden" name ="user" value="<%= URLDecoder.decode(request.getParameter("key"),"utf-8")%>" /> 
	</form>
	
	<form method="post" name="form2" action="doaction" id="loyoen">
	    <input id = 'test2' type = 'hidden' name="test2"> 
	</form>
  </body>
</html>
