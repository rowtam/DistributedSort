import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.Vector;
import java.util.Enumeration;

/**
 * Viewer for a CS 342 Sort.  Requires that user send messages over a
 * socket with the following contents, each on a separate line:
 *       sort type (see Sort_Request_Base.h for definitions)
 *       status (see Sort_Request_Base.h for definitions)
 *       number of elements in the array
 *       array elements (integers printed as character strings), one per line
 *  The information is then broadcast to all registered SortListeners.
 *
 *
 * The default port is 3420.  It may be overridden with the -port option.
 *
 * @author      David L. Levine
 * @author      Chris Lane
 * @author      John Heitmann
 * @version     $Revision: 1.3 $
 */
public class Sort_Viewer extends Frame  {

  public static final int kHistogramViewer = 1;
  public static final int kOriginalViewer = 2;


  private static int port = 3420;

  private Vector sortListeners;

  // ViewType allows users to choose which viewer to use.
  Sort_Viewer (int viewType) {
    super ();

    // To terminate the viewer when the Close button is pressed:
    addWindowListener (new WindowAdapter() {
      public void windowClosing (WindowEvent we) {
        System.exit (0);
      }
    });

    if (viewType == kHistogramViewer)
      setSize (600, 400);
    else
      setSize (425, 680);


    setTitle ("Sort_Viewer");

    sortListeners = new Vector(2);

    if (viewType == kHistogramViewer){
      SortHistogram viewer = new SortHistogram ();
      addSortListener( viewer );
      add(viewer);
    }
    else{
      OriginalSortViewer viewer = new OriginalSortViewer ();
      addSortListener( viewer );
      add(viewer);
    }

    MenuBar menubar = new MenuBar ();
    Menu menu = new Menu ( "Sort_Viewer" );
    MenuItem quit = new MenuItem ( "Quit" );
    quit.setEnabled (true);
    menu.add (quit);
    menubar.add (menu);
    setMenuBar (menubar);

    quit.addActionListener (
      new ActionListener () {
        public void actionPerformed (ActionEvent e) {
          System.exit (0);
        }
      }
    );
    setVisible (true);
  }

  //Registers a new SortListener.
  public void addSortListener(SortListener l){
    sortListeners.addElement(l);
  }

  //Notifies all observers that a sortEvent occurred.
  public void publishSortUpdate(SortEvent e){
    for (Enumeration iterator = sortListeners.elements();
          iterator.hasMoreElements();){
      SortListener l = (SortListener)iterator.nextElement();
      l.sortPerformed(e);
    }
  }

  public void displayHostname (String hostname) {
    setTitle (hostname);
  }


  public static void main (String[] args) {
    int arg_index = 0;

    // Process command line arguments.
    while (args.length > arg_index) {

      if ((args[arg_index].equals ("-port")) &&
          (args.length > arg_index + 1))
        {
          port = Integer.parseInt (args[arg_index + 1]);
          System.out.println ("Sort_Viewer.java; Listen on port " + port);
          arg_index += 2;
        }
      // Skip over anything else
      else
        {
          System.err.println ("Sort_Viewer.java; Skipping argument [" +
                              args[arg_index] + "]");
          ++arg_index;
        }
      }

    Sort_Viewer sortViewer = new Sort_Viewer (kHistogramViewer);

    Listener listener = new Listener (sortViewer,  port);
    new Thread(listener).start(); // Spawn a new thread to handle networking.
                                  // Listener should spawn a new thread for
                                  // every connection, but that would mean
                                  // multiple viewers also.
  }
}


/**
 * Listener socket for Sort_Viewer.  It accepts a connection,
 * then waits for messages with content described above.
 *
 * The default port is 3420.  It may be overridden with the -port option.
 *
 * @author      David L. Levine
 * @author      John Heitmann
 * @version     $Revision: 1.3 $
 */
class Listener implements Runnable{

  Sort_Viewer sortViewer;
  int port;

  Listener (Sort_Viewer s, int port) {
        sortViewer =  s;
        this.port = port;
  }

  public void run () {
    ServerSocket serverSocket = null;
    try {
      serverSocket = new ServerSocket (port);
    } catch (IOException exception) {
      System.err.println ("Sort_Viewer.java; The socket to receive "+
                          "connections couldn't be made:");
      System.err.println (exception);
    }

    while (true) {
      try {
        Socket socket = serverSocket.accept ();
        BufferedReader input =
          new BufferedReader (
            new InputStreamReader (socket.getInputStream ()));
        sortViewer.displayHostname ("Accepted connection from " +
          socket.getInetAddress ().getHostName ());

        while (true) {
          String string = input.readLine ();

          if (string == null  ||  string.equals ("DISCONNECT")) {
            break;
          }

          try {
            // Read the actual data from the stream.
            int sortType = 0;
            string = input.readLine ();
            int status = 0;
            string = input.readLine ();
            int numItems = Integer.parseInt (string);

            // Assume that the data are integers.
            int[] array = new int[numItems];
            for (int i = 0; i < numItems; ++i)
              array[i] = Integer.parseInt(input.readLine ());

            // Now broadcast the info to all Listeners.
            sortViewer.publishSortUpdate(new SortEvent (sortType,
                                                        status,
                                                        array));
          } catch (NumberFormatException exception) {
            System.err.println ("\n\nSort_Viewer.java; Listener.run (): ");
            System.err.println (exception);
            System.err.println ("Likely cause:  your Sort_Info.print () " +
              "does not use the expected format.\nSee comments at top " +
              "of Sort_Viewer.java\n");
            System.exit (-1);
          }
        }

        socket.close ();
        sortViewer.displayHostname ("Sort_Viewer");
      } catch (IOException exception) {
        System.err.println ("Sort_Viewer.java; Listener.run (): ");
        System.err.println ("An error occured reading data from "+
                            "the remote host:");
        System.err.println (exception);
      }
    }
  }
}

/**
 * SortHistogram displays an array of ints in a bar graph style. It should
 * be listening (read: 'Observing') to a source which is sending partially
 * sorted or sorted data. After instantiation, only sortPerformed need be
 * called to notify SortHistogram of the change. This class should be
 * registered as a listener in another class in the same manner as event
 * listeners.
 * This is automagically double buffered from its parent.
 *
 * @author  John Heitmann
 * @version $Revision: 1.3 $
 */
class SortHistogram extends DoubleBufferedCanvas implements SortListener{

  //various color constants for use in drawing
  private static Color barColor = Color.blue;
  private static Color hiliteColor = Color.red; //unused as of now
  private static Color backgroundColor = Color.white;

  private int[] hiliteArray;    //unused as of now
  private int[] data;           //the array itself
  private int max;              //max value in the array

  SortHistogram(){
    super();
    data = new int[0];
    setBackground ( backgroundColor );
    repaint();
  }

  //The observer method of this class
  public synchronized void sortPerformed(SortEvent e){
    data = e.array;

    //find the max value in the array so we can
    //scale the display accordingly
    max = Integer.MIN_VALUE;
    for (int i = 0; i < e.array.length; ++i)
      max = Math.max( max, e.array[i]);
    repaint();
  }


  //inherited from DoubleBufferedCanvas
  public void drawMyself (Graphics g) {

    //erase the old stuff
    g.setColor (backgroundColor);
    g.fillRect (0, 0, width, height);

    //calculate important variables for use in the loop
    int fontHeight = fontMetrics.getHeight()-2;
    int bottomAreaHeight = fontHeight*( (""+max).length() );
    height -= bottomAreaHeight;

    //draw each bar + label
    for (int i = 0; i < data.length; ++i){

      double barWidthDouble = (double)width/(double)data.length;
      int barWidth = (int)barWidthDouble;
      int barHeight = (int)((double)data[i] *
                      ((double)height/(double)max));

      //first draw in the item numbers
      g.setColor(Color.black);
      String num = Integer.toString(data[i]);


      int maxNum = width/7;
      int modValue = data.length/maxNum;
      modValue = Math.max(1, modValue);  //prevents div by zero
      // Figure out how many numbers can fit along the bottom.
      if (i % modValue == 0)
        for (int j = 0; j < num.length(); ++j) {
          int xLoc = (int)(i*barWidthDouble + barWidthDouble/2) -
                     fontMetrics.charWidth('0')/2;
          int yLoc = (j+1) * fontHeight + height;
          g.drawString(""+num.charAt(j), xLoc, yLoc );
        }

      //draw the bar
      g.setColor( barColor );
      g.fillRect( (int)(i*barWidthDouble),    //xcoord
                  height-barHeight,           //ycoord
                  barWidth,                   //width
                  barHeight);                 //height

      //draw a fringe around the bar
      g.setColor( barColor.darker().darker() );
      g.drawRect( (int)(i*barWidthDouble+1),  //xcoord
                  height-barHeight,           //ycoord
                  barWidth-3,                 //width
                  barHeight);                 //height
      g.setColor( barColor.darker() );
      g.drawRect( (int)(i*barWidthDouble+2),  //xcoord
                  height-barHeight+1,         //ycoord
                  barWidth-5,                 //width
                  barHeight-1);               //height

      //add some whitespace between the bars
      if ( barWidth > 4 ){
        g.setColor( Color.white );
        g.drawLine( (int)(i*barWidthDouble),  //x1
                    0,                        //y1
                    (int)(i*barWidthDouble),  //x2
                    height);                  //y2
        g.drawLine( (int)((i+1)*barWidthDouble-1),  //x1
                    0,                        //y1
                    (int)((i+1)*barWidthDouble-1),   //x2
                    height);                  //y2

      }
    }
    height += bottomAreaHeight;  //fix an earlier cludge
  }
}

/**
 * OriginalSortViewer was the viewer which originally came with the lab. It
 * prints out the array in a stack like fashion. It should
 * be listening (read: 'Observing') to a source which is sending partially
 * sorted or sorted data. After instantiation, only sortPerformed need be
 * called to notify OriginalSortViewer of the change. This class should be
 * registered as a listener in another class in the same manner as event
 * listeners.
 * This is automagically double buffered from its parent.
 *
 * @author  John Heitmann
 * @version $Revision: 1.3 $
 */
class OriginalSortViewer extends DoubleBufferedCanvas implements SortListener{

  static Color foregroundColor = Color.yellow;
  static Color backgroundColor = new Color (0x00, 0x6d, 0xaa);

  //the array itself
  private int[] data;

  OriginalSortViewer (){
    super ();
    data = new int[0];
    setBackground ( backgroundColor );
    repaint();
  }

  public void sortPerformed ( SortEvent e ){
    data = e.array;
    repaint ();
  }

  public void drawMyself ( Graphics g ){

    //erase the old stuff
    g.setColor (backgroundColor);
    g.fillRect (0, 0, width, height);

    //The rest is basically copied and pasted from version 1.0
    g.setColor ( foregroundColor );

    if (data.length > 30) {
      int posy = 25;
      for (int i = data.length; i > (data.length - 30) ; i--) {
        g.drawRect (20, (posy += 25), 300, 20);
        g.drawString (""+data[(i - 1)], 40, posy + 15);
        // if (i == (data.length - 1)) {
        //   g.drawString ("Top 30 elements in Sort", 500, 30);
        // }
      }
    } else {
      int posy = 680;
      for (int i = 1; i <= data.length; ++i) {
        g.drawRect (20, (posy -= 25), 400, 20);
        g.drawString (""+data[(i - 1)], 40, posy + 15);
        //  g.drawString ("Last element in Sort", 150, 590);
        //  if (i == data.length) {
        //    g.drawString ("First element in Sort", 500, posy);
        //  }
      }
    }
  }
}


/**
 * DoubleBufferedCanvas is an abstract base class which is used to facilitate
 * the creation and use of an offscreen double buffer for drawing. Using double
 * buffering eliminates flicker in animated drawing by blitting the image all
 * at once instead of bit by bit.
 * Only drawMyself() should be implemented in the base class. Note that
 * the only out of the ordinary thing drawMyself() must do is erase the old
 * image.
 *
 * @author     John Heitmann
 * @version    $Revision: 1.3 $
 */

abstract class DoubleBufferedCanvas extends Canvas{

  //used in drawing offscreen
  protected Image offImage;
  protected Graphics offGraphics;
  protected FontMetrics fontMetrics;

  //width and height of the screen,
  //these are global in order to detect
  //a resize in which case we must create
  //a new off screen image
  protected int width,height;

  public abstract void drawMyself(Graphics g);

  public void paint( Graphics g){
    update(g);
  }

  //update utilized for double buffering
  public void update (Graphics g) {
    if (offGraphics == null ||
      getSize().width != width ||
      getSize().height != height){
          offImage = createImage( getSize().width, getSize().height );
          offGraphics = offImage.getGraphics();
          fontMetrics = offGraphics.getFontMetrics();
          width = getSize().width;
          height = getSize().height;
    }

    drawMyself(offGraphics);

    g.drawImage(offImage, 0, 0, this);  //blit to the screen
  }
}



/**
 * SortListeners are observers which wait for new/updated
 * arrays to be sent to them.
 *
 * @author     John Heitmann
 * @version    $Revision: 1.3 $
 */
interface SortListener{

  public abstract void sortPerformed(SortEvent e);

}

/**
 * SortEvent mirrors Sort_Info<int>:  it is a message containing
 * an array, and info about that array for observers to act upon.
 *
 * @author     John Heitmann
 * @version    $Revision: 1.3 $
 */
class SortEvent {

  int[] array;
  int sortType;
  int status;

  SortEvent(int sortType, int status, int[] array){
    this.sortType = sortType;
    this.status = status;
    this.array = array;
  }
}
