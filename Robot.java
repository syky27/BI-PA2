package robot;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;

class ServerThread extends Thread {

    Socket socket;
    Integer ID;
    PrintWriter out = null;
    InputStream in = null;
    String clientName;

    ArrayList<String> logArray;

    public ServerThread(Socket socket, Integer ID) throws IOException {
        this.ID = ID;
        this.socket = socket;
        this.out = new PrintWriter(socket.getOutputStream());
        this.in = new DataInputStream(socket.getInputStream());

    }


    public String getClientsName() {
        return this.clientName;
    }


    
    
    public boolean getMessage() throws Exception {
        String message = new String( );
        int character = 0;
        for (int d = 0; d < 5; ++d ) { 
            character = in.read(); 
            message += (char)character; 
        
        
            if (!message.startsWith("I") && !message.startsWith("F")){ 
                passToRobot("501");
                return false; 
            }
        }
        
        switch (message) {
            case "INFO ":
                try {
                    while ( true ) {
                        character = in.read();
                        if (character == 13) 
                        {
                            character = in.read();
                            while (character == 13)     
                                character = in.read();

                            if (character == 10) {
                                passToRobot("202");
                                return true;
                            }
                       }
                       
                } 
                 } catch (Exception e) { e.getMessage();  passToRobot("501");}
                
                
            case "FOTO ":
                  getFoto();
                break;
                
                
            default: 
                passToRobot("501");     
                return false;
        }
        
        return true;
    }
    
    
    

    

    public int getPassword() throws Exception {
        String message = "";
        int currentChar;
        while (!message.endsWith("\r\n")) {
            currentChar = in.read();
            message += (char) currentChar;
        }

        if ("\r\n".equals(message)) {
            return -1;
        }

        message = message.substring(0, message.length() - 2);
        return Integer.parseInt(message);
    }

    public int checkPasswd() throws Exception {
        int nick, password;
        passToRobot("200");
        nick = getNick();
        passToRobot("201");

        try {
            password = getPassword();
            if (password == -1 || nick == -1 || password != nick) {
                return -1;
            }
        } catch (Exception e) {
            return -1;
        }

        passToRobot("202");
        return 1;
    }

    public void passToRobot(String code) {
        switch (code) {
            case "201":
                out.write("201 PASSWORD\r\n");
                out.flush();
                break;
                
            case "200":
                out.write("200 LOGIN\r\n");
                out.flush();
                break;
                
            case "202":
                out.write("202 OK\r\n");
                out.flush();
                break;
                
            case "501":
                out.write("501 SYNTAX ERROR\r\n");
                out.close();
                try {socket.close();} catch (IOException e1) {System.out.println("Cannot close socket");}
                break;
                
            case "500":
                out.write("500 LOGIN FAILED\r\n");
                out.close();
                try {socket.close();} catch (IOException e1) {System.out.println("Cannot close socket");}
                break;
                
            case "Read timed out":
                out.write("502 TIMEOUT\r\n");
                out.close();
                try {socket.close();} catch (IOException e1) {System.out.println("Cannot close socket");}
                break;
                
            case "502":
                out.write("502 TIMEOUT\r\n");
                out.close();
                try {socket.close();} catch (IOException e1) {System.out.println("Cannot close socket");}
                break;
                
                    
                
            case "300":
                out.write("300 BAD CHECKSUM\r\n");
                out.close();
        }
    }

    public int getNick() throws Exception {
        String message = new String();
        int currentInput;
        int sumMessage = 0;
        int cycle = 0;
        
        try {
            while (!message.endsWith("\r\n") && cycle != 5) {
                currentInput = in.read();
                ++cycle;
                sumMessage += currentInput;
                message += (char) currentInput;
            }

            if ("\r\n".equals(message)) {
                return -1;
            }
            if (!"Robot".equals(message)) {
                while (!message.endsWith("\r\n")) {
                    currentInput = in.read();
                    message += (char) currentInput;
                }
                return -1;
            }

            while (true) {
                currentInput = in.read();

                if (currentInput == 13)
                {
                    sumMessage += 13;
                    currentInput = in.read();
                    while (currentInput == 13) {
                        sumMessage += 13;
                        currentInput = in.read();

                    }

                    if (currentInput == 10) {
                        return sumMessage - 13;
                    }

                }

                sumMessage += currentInput;
            }
        } catch (Exception e) {
            return -1;
        }

    }

    @Override
    public void run() {
             try 
             {
                 this.socket.setSoTimeout(45000);
                 
                    int didItPass = checkPasswd();
                   
                    if (didItPass == -1)  {
                        passToRobot("500");
                        out.close();
                        return;
                    }
                    
                    while (true) {                     
                        
                        if (!getMessage()) {
                            break;
                        }
                 }
                    
                    
                    
                    
                    
             } catch (NumberFormatException e) {
                 passToRobot("501");
                 out.close();
             } 
             catch (Exception e) {
                 if (e.getMessage().equals("NullPointerException")) {
                     System.out.println("NULL POINTER EXCEPTION YOU ARE V PICI");
                 }
                    System.out.println("Fucked Up SHIT");
                    passToRobot("502");
              } 
             
                
    }

    private boolean getInfo(String typeOfMessage) throws IOException {
        int character = 0;
        
        
                
                    while ( true ) {
                        character = in.read();
                        System.out.println((char)character);
                        
                        if (character == 13) 
                        {
                            character = in.read();
                            while (character == 13){
                               character = in.read();
                            }

                            if (character == 10) {
                                System.out.println((char)character);
                                return true;
                            }
                       }
                       
                } 
    }

    private boolean getFoto() throws IOException {
        String message = new String();
        int bytes = 0;
        int character;
        
        // Will read until space
        while (!message.contains(" ")) {
            // load one character in decimal
            character = in.read();
            
            if (character == -1) {
                System.out.println("DEBUG character == -1");
                passToRobot("501");
                
            }
            // add numeric char to message.. nukmber of bytes
            message += (char)character;
            if(((char)character < '0' || (char)character > '9') && (char)character != ' '){
                System.out.println("Number of bytes is not numeric");
                passToRobot("501");
                return false;
            }
        }
        
        bytes = Integer.parseInt(message.replaceAll(" ", ""));
        
        //tohle by melo odchytnou to checkovani toho jestli to je cislo, ale protoze
        //to dela bordel tak tahle to bude jistejsi
        if (bytes <= 0) {
            System.out.println("Bytes are smaler or nul");
            passToRobot("501");
            return false;
        }
        
        ArrayList<Integer> dataOfPhoto = new ArrayList<>();
        
       
        
        int checksum = 0;
        int iteratorOverBytes = 0;
         
         
        while (true) {            
            character = in.read();
            iteratorOverBytes ++ ;
            checksum += character;
           
            
            if (character == -1) {
                dataOfPhoto.clear();
                break; 
            }
             
            message += (char) character;
           dataOfPhoto.add(character);
           
            if (iteratorOverBytes == bytes) {
                break;
            }
            
            
            
        }
        
        DataInputStream lastBullshit;
        lastBullshit = new DataInputStream(this.socket.getInputStream());
        
        int lb = lastBullshit.readInt();
        
        if (checksum != lb) {
            passToRobot("300");
            return false;
        }
        
        
        if(dataOfPhoto.size() != checksum){
            passToRobot("501");
            return false;
        }
        
        
        //save photo...
        
        
        
        
        
        dataOfPhoto.clear();
        passToRobot("202");
        return true;
    }

}


                
                
        
        
    
    
    

    
    
    


class Server extends Thread {

    Integer port;

    public Server(int port) {
        this.port = port;
    }

    @Override
    public void run() {
        ServerSocket socket = null;
        Socket acceptedSocket;

        try {
            socket = new ServerSocket(this.port);
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Exception Caught");
        }

        if (socket == null) {
            try {
                socket = new ServerSocket();
            } catch (IOException e) {
                e.printStackTrace();
                System.out.println("Memory insufficient");
            }
        }
        try {
            socket.setSoTimeout(0);
        } catch (SocketException e) {
            e.printStackTrace();
            System.out.println("Fucked up socket timeout");
        }
        System.out.println("Server Starting");
        Integer counter = 0;

        try {
            while (true) {

                acceptedSocket = socket.accept();

                System.out.println("Socket Accepted");
                ServerThread karel = new ServerThread(acceptedSocket, counter);
                karel.start();
                System.out.println("Up and Running");
                counter++;
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}

class TemplateServer {

    public static void svr_main(int port) throws IOException {
        System.out.println("Starting server on port " + port + " FEKAAAAAALLLLLL");
        Server server = new Server(port);
        server.start();
    }
}

public class Robot {

    public static void main(String[] args) throws IOException {
        if (args.length == 1) {
            System.out.println("Starting server...FEKAL\n");
            TemplateServer server = new TemplateServer();
            server.svr_main(Integer.parseInt(args[0]));
        } else {
            TemplateServer server = new TemplateServer();
            server.svr_main(Integer.parseInt("3373"));
            System.err.println("Client: java robot.Robot <hostname> <port>");
            System.err.println("Server: java robot.Robot <port>");
//            System.exit(1);
        }

    }
}