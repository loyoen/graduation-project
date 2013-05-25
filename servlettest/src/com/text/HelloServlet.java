package com.text;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Stack;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import java.sql.*;
import java.net.*;

public class HelloServlet extends HttpServlet {
	

	
	int count=0;
	FileWriter fr = null;
	FileReader fread = null;
	BufferedReader br=null;
	Stack<String> empkey = null;
	int chosestack=-1;
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
		throws ServletException, IOException {
	// TODO Auto-generated method stub
		Connection ct=null;
        Statement  sm=null;
        ResultSet  rs=null;
        System.out.println("\n");
        System.out.println(count);
        System.out.println("\n");
        //req.setCharacterEncoding("UTF-8");
        //resp.setContentType("text/html;charset=UTF-8");
        int swit=-1;
        try
        {
        	//String u=req.getParameter("usrename");
        	//String p=req.getParameter("passwd");
        	String txtMsg = req.getParameter("test2"); 
        	//String txtMsg = new String(req.getParameter("test2").getBytes("iso-8859-1"),"utf-8");
        	

            if(txtMsg!=null)
            {
            	txtMsg = new String(txtMsg.getBytes("iso-8859-1"),"utf-8");
                System.out.println(txtMsg);
            	swit=1;
            }
           // Class.forName("com.mysql.jdbc.Driver").newInstance();  
           // ct=DriverManager.getConnection("jdbc:mysql://localhost:3306/googledatabase","root","loyoen");
           // sm=ct.createStatement();
            
            if(swit==1)
            {
            	
            	//sm.executeUpdate("insert into ans values('张三','20','男',11,'man',"+count+")");
            	if(empkey==null)
            		empkey=new Stack<String>();
            	if(txtMsg.charAt(0)=='0')
            	{
            		String t[] = txtMsg.split("\n");
            		empkey.push(t[2]);
            	}
            	else
            	{
            	
	            	if(fr==null)
	            		fr = new FileWriter("C:\\Users\\Zenas\\Desktop\\loyoen\\loyoen\\test.txt",true);
	            	fr.write(txtMsg);
	            	fr.flush();
            	}
            	Thread.sleep(2000);
            	//return;
            }
            
            /*
            count++;
            rs=sm.executeQuery("select * from keyword where id="+count);
            */
            String key="";
            if(chosestack==-1)
            {
	            if(fread ==null)
	            {
	            	fread = new FileReader("C:\\Users\\Zenas\\Desktop\\loyoen\\loyoen\\keytoday.txt");
	            	br = new BufferedReader(fread);
	            }
	            key = br.readLine();
	            System.out.println(key);
	            if(key!=null)
	            {
		        	String key1 = java.net.URLEncoder.encode(java.net.URLEncoder.encode(key,"utf-8"),"utf-8");
		        	resp.sendRedirect("Login.jsp?key="+key1);
	            }
	          /*  if(rs.next())                
	            {
	            	key=rs.getString(1);
	            	System.out.println(key);
	
	            	//req.setAttribute("key", key);
	            	//RequestDispatcher rd=req.getRequestDispatcher("/Login.jsp");
	            	//rd.forward(req, resp);
	            	String key1 = java.net.URLEncoder.encode(java.net.URLEncoder.encode(key,"utf-8"),"utf-8");
	            	resp.sendRedirect("Login.jsp?key="+key1);
	            	//resp.sendRedirect("../Login.jsp");
	            }
	            */
            }
          if(key==null||chosestack==1)
          {
        	  if(!empkey.empty())
        	  {
        		  chosestack=1;
        		  key=empkey.pop();
        		  String key1 = java.net.URLEncoder.encode(java.net.URLEncoder.encode(key,"utf-8"),"utf-8");
		          resp.sendRedirect("Login.jsp?key="+key1);
        	  }
        	  else
        	  {
        		  if(fr!=null)
        			  fr.close();
	        	  if(br!=null)
	        		  br.close();
	        	  if(fread!=null)
	        		  fread.close();
        	  }
          }
        }catch(Exception ex)
        {
              ex.printStackTrace();
        }finally {
            try {
                if(rs != null) {
                    rs.close();
                    rs = null;
                }
                if(sm != null) {
                    sm.close();
                    sm= null;
                }
                if(ct != null) {
                    ct.close();
                    ct = null;
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
 
        
	}
	
	void dealmessage(String msg)
	{
		
	}
 
}