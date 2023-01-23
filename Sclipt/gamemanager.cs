using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class gamemanager : MonoBehaviour
{
    UIScriptNow uiscriptnow;
    UIScriptNext uiscriptnext;
    ParentObj parent;
    ParentObjeLift parentlift;
    Spawner spawner;//スポナー
    Block activeBlock;//生成されたブロック格納
    [SerializeField] public GameObject Block_T;
    [SerializeField] public GameObject BlockCan;
    [SerializeField] private float dropInterval = 0.25f;//次にブロックが落ちるまでのインターバル時間
    float nextdropTimer;//次にブロックが落ちるまでの時間

    [SerializeField] private float transformR ;
    [SerializeField] private float transformL ;

    public float roteL=0;
    public bool rotechng=default;
    bool RoteR = default;
    bool RoteL = default;
   private bool Bottom =false;
    private bool BottomON = false;
    public bool SperL = false;

    //ボードのスクリプトを格納
    Board board;
    //Maxタイマー
    float MoveTime =10f;
    //底カウント
    float Count =0f;
    //入力受付タイマー(3種類)
    float nextKeyDownTimer, nextKeyLeftRightTimer, nextKeyRotateTimer;
    //入力インターバル(3種類)
    [SerializeField] private float nextKeyDownInterval, nextKeyReftLightInterval, nextKeyRotateInterval;

    //  パネルに格納
    [SerializeField] private GameObject gameOverPanel;
    public AudioClip Rsound;
    public AudioClip Lsound;
    public AudioClip Rotsound;
    public AudioClip Psound;
    public AudioClip Dsound;

    AudioSource audioSource;
   
    bool gameOver;

    //スポナーオブジェクトをスポナー変数に格納するコードの追記
    private void Start()
    {
       
        spawner = GameObject.FindObjectOfType<Spawner>();//スポナークラスからブロック生成関数を読んで半数に格納する
        board = GameObject.FindObjectOfType<Board>();
        audioSource = GetComponent<AudioSource>();
        uiscriptnow = GameObject.FindObjectOfType<UIScriptNow>();
        uiscriptnext = GameObject.FindObjectOfType<UIScriptNext>();

        spawner.transform.position = Rounding.Round(spawner.transform.position);

        //タイマーの初期設定
        nextKeyDownTimer = Time.time + nextKeyDownInterval;
        nextKeyLeftRightTimer = Time.time + nextKeyReftLightInterval;
        nextKeyRotateTimer = Time.time + nextKeyRotateInterval;

        if (!activeBlock)
        {
            activeBlock = spawner.SpawnBlock();

        }

        //ゲームオーバーパネルの非表示設定
        if(gameOverPanel.activeInHierarchy)
        {
            gameOverPanel.SetActive(false);
        }

    }

    private void Update()
    {

        if (gameOver)
        {
            return;
        }
        PlayerInput();
        uiscriptnext.SpriteNext();
        uiscriptnow.Sprite();
       

    }
    void PlayerInput()
    {
        parent = GameObject.FindObjectOfType<ParentObj>();
        parentlift = GameObject.FindObjectOfType<ParentObjeLift>();
        float hori = Input.GetAxis("Horizontal");
        float vert = Input.GetAxis("Vertical");
        if (Input.GetKey(KeyCode.D) && (Time.time > nextKeyLeftRightTimer) || Input.GetKeyDown(KeyCode.D) || (hori > 0) && (Time.time > nextKeyLeftRightTimer))
        {
          
            activeBlock.MoveRight();//右に動かす

            nextKeyLeftRightTimer = Time.time + nextKeyReftLightInterval;

            if (!board.CheckPosition(activeBlock))
            {
                activeBlock.MoveLeft();
            }
            audioSource.PlayOneShot(Rsound);
        }
        else if (Input.GetKey(KeyCode.A) && (Time.time > nextKeyLeftRightTimer) || Input.GetKeyDown(KeyCode.A) || (hori < 0) && (Time.time > nextKeyLeftRightTimer))
        {
            activeBlock.MoveLeft();//左に動かす

            nextKeyLeftRightTimer = Time.time + nextKeyReftLightInterval;

            if (!board.CheckPosition(activeBlock))
            {

                activeBlock.MoveRight();
            }
            audioSource.PlayOneShot(Lsound);
        }
        else if (Input.GetKey(KeyCode.E) && (Time.time > nextKeyRotateTimer) || Input.GetKey("joystick button 2") && (Time.time > nextKeyRotateTimer))
        {
         
            RoteR = true;
            rotechng = false;
            nextKeyRotateTimer = Time.time + nextKeyRotateInterval;
            transformR = board.transform.localEulerAngles.z;
           
            activeBlock.RotateRight();
            if (!board.CheckPosition(activeBlock))
            {
                activeBlock.RotateLeft();
            }
            if (Bottom == true )  
            {
               
                transformL = board.transform.localEulerAngles.z;
                RoteSarcth();


             }

            audioSource.PlayOneShot(Rotsound);
        }
        else if (Input.GetKey(KeyCode.E) && (Time.time > nextKeyRotateTimer) || Input.GetKey("joystick button 3") && (Time.time > nextKeyRotateTimer))
        {
           
            RoteL = true;
            rotechng = false;
            activeBlock.RotateLeft();
            nextKeyRotateTimer = Time.time + nextKeyRotateInterval;
            transformR = board.transform.localEulerAngles.z;
            Vector3 posi = board.transform.position;
          if (!board.CheckPosition(activeBlock))
            {
                activeBlock.RotateRight();
            }
            if (Bottom == true )
            {
              
                
                RoteSarcth();

             }

            audioSource.PlayOneShot(Rotsound);

        }
        else if (Input.GetKey("joystick button 3") && (Time.time > nextKeyRotateTimer))
        {
      
            spawner.HoldOn = true;
        }
        else if (Input.GetKey(KeyCode.S) && (Time.time > nextKeyDownTimer) || (Time.time > nextdropTimer) || Input.GetKey("joystick button 1") && (Time.time > nextKeyDownTimer) || (Time.time > nextdropTimer))
        {
            activeBlock.MoveDown();//   下に動かす
            Bottom = false;
            nextKeyDownTimer = Time.time + nextKeyDownInterval;
            nextdropTimer = Time.time + dropInterval;

            if (!board.CheckPosition(activeBlock))
            {
                if (board.OverLimit(activeBlock))
                {
                    GameOver();
                }
                else
                {

                    if (Count >= MoveTime)
                    {
                        board.destroy = false;
                        //そこについた時の処理
                        BottomON = true;
                          BottomBoard();
                        


                    }
                    else
                    {
                        Count++;
                       
                        BottomBoard();
                    }

                }

            }
        }

    }
    void RoteSarcth()
    { 

        rotechng = true;
        parentlift.ParentLift();
        if (RoteR==true)
        {
  

            switch (transformR)
            {
                case 0:
                    break;
                case 270:
                    activeBlock.MoveLeft();
                    activeBlock.MoveDown();
                   
                    parent.Parent();
                    RoteSercthSecnd();
                    break;
                case 90:
                    activeBlock.MoveLeft();
                    activeBlock.MoveDown();
                   
                    RoteSercthSecnd();
                    break;
                case 180:
                    activeBlock.MoveRight();
                    activeBlock.MoveDown();
                   
                    parent.Parent();
                    RoteSercthSecnd();
                    break;
                default:

                    activeBlock.MoveLeft();
                    activeBlock.MoveDown();

                    parent.Parent();
                    RoteSercthSecnd();
                    break;
            }
        }
        if (RoteL==true)
        {
          
            switch (transformR)
            {
                case 0:
                    break;
                case -90:
                    activeBlock.MoveRight();
                    activeBlock.MoveDown();
                  
                    parent.Parent();
                    RoteSercthSecnd();
                    break;
                case -180:
                    activeBlock.MoveRight();
                    activeBlock.MoveDown();
                   
                    parent.Parent();
                    RoteSercthSecnd();
                    break;
                case -270:
                    activeBlock.MoveRight();
                    activeBlock.MoveDown();
                   
                    parent.Parent();
                    RoteSercthSecnd();

                    break;
                default:

                    activeBlock.MoveRight();
                    activeBlock.MoveDown();

                    parent.Parent();
                    RoteSercthSecnd();

                    break;
            }
        }
    }
    void RoteSercthSecnd()
    {
        if (!board.CheckPosition(activeBlock))
        {
            roteL =0;
            if (RoteR == true)
            {
                for (int i = 0; i <= 4 || BottomON == false; i++)
                {
                   roteL = +90;
                    switch (roteL)
                    {
                        case 0:
                            RoteSercthSerd();
                            break;
                        case 270:

                            activeBlock.MoveUp();
                            RoteSercthSerd();

                            break;
                        case 90:

                            activeBlock.MoveUp();
                            RoteSercthSerd();

                            break;
                        case 180:

                            activeBlock.MoveDown();
                            RoteSercthSerd();

                            break;
                        default:

                            activeBlock.MoveUp();
                            RoteSercthSerd();

                            break;
                    }
                }
               
            }
            if (RoteL == true)
            {
                for (int i = 0; i <= 4 || BottomON == false; i++)
                {
                    roteL = -90;
                    switch (roteL)
                    {
                        case 0:
                            RoteSercthSerd();
                            break;
                        case -270:

                            activeBlock.MoveUp();
                            RoteSercthSerd();

                            break;
                        case -90:

                            activeBlock.MoveUp();
                            RoteSercthSerd();

                            break;
                        case -180:

                            activeBlock.MoveDown();
                            RoteSercthSerd();

                            break;
                        default:

                            activeBlock.MoveUp();
                            RoteSercthSerd();

                            break;
                    }
                }
            }
           

         }
    }
    void RoteSercthSerd()
    {
        Vector3 posi = board.transform.position;
        roteL = 0;
        if (RoteR == true)
        {
           
            for (int i = 0; i <= 4|| BottomON == false; i++)
            {
                roteL = +90;
                switch (roteL)
                {
                    case 0:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, 2, 0));
                        RoteSercthForce();

                        break;
                    case 270:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, -2, 0));
                        RoteSercthForce();

                        break;

                    case 90:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, -2, 0));
                        RoteSercthForce();

                        break;
                    case 180:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, 2, 0));
                        RoteSercthForce();

                        break;
                    default:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, -2, 0));
                        RoteSercthForce();

                        break;
                }
            }
        }
        if (RoteL == true)
        {
            for (int i = 0; i <= 4 || BottomON == false; i++)
            {
                roteL = -90;
                switch (roteL)
                {
                    case 0:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, 2, 0));
                        RoteSercthForce();

                        break;
                    case -270:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, -2, 0));
                        RoteSercthForce();

                        break;

                    case -90:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, -2, 0));
                        RoteSercthForce();

                        break;
                    case -180:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, 2, 0));
                        RoteSercthForce();

                        break;
                    default:
                        SperL = true;
                        board.transform.position = posi;
                        activeBlock.Move(new Vector3(0, -2, 0));
                        RoteSercthForce();

                        break;
                }
            }
        }
    }
    void RoteSercthForce()
    {
        rotechng = true;
        parentlift.ParentLift();
        roteL = 0;
        if (RoteR == true)
        {
            for (int i = 0; i <= 4 || BottomON == false; i++)
            {
                roteL = +90;
                switch (roteL)
                {
                    case 0:
                        SperL = true;
                        activeBlock.MoveRight();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;
                    case 270:
                        SperL = true;
                        activeBlock.MoveLeft();
                        activeBlock.MoveDown();
                       rotechng = true;
                        parent.Parent();
                       
                        break;

                    case 90:
                        SperL = true;
                        activeBlock.MoveLeft();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;
                    case 180:
                        SperL = true;
                        activeBlock.MoveRight();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;

                    default:
                        SperL = true;
                        activeBlock.MoveLeft();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();

                        break;


                }
            }
        }
        if (RoteL == true)
        {
            for (int i = 0; i <= 4 || BottomON == false; i++)
            {
                roteL = -90;
                switch (roteL)
                {
                    case 0:
                        SperL = true;
                        activeBlock.MoveRight();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;
                    case -270:
                        SperL = true;
                        activeBlock.MoveLeft();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;

                    case -90:
                        SperL = true;
                        activeBlock.MoveLeft();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;
                    case -180:
                        SperL = true;
                        activeBlock.MoveRight();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();
                        break;

                    default:
                        SperL = true;
                        activeBlock.MoveLeft();
                        activeBlock.MoveDown();
                        rotechng = true;
                        parent.Parent();

                        break;
                }
            }
        }
    }

    //ボードの底についた時に次のブロックを生成する関数
    void BottomBoard()
    {
        Bottom = true;
        rotechng = false;
        activeBlock.MoveUp();
        if(BottomON==true)
        {
             board.SaveBlockInGrid(activeBlock);

            activeBlock = spawner.SpawnBlock();
            roteL = 0;
            nextKeyDownTimer = Time.time;
            nextKeyLeftRightTimer = Time.time;
            nextKeyRotateTimer = Time.time;

            board.ClearAllRows();//埋まっていれば削除する
            Count = 0f;
            audioSource.PlayOneShot(Psound);
            if (board.destroy == true)
            {
                audioSource.PlayOneShot(Dsound);
            }
            BottomON = false;
        }
       

      
        
    }
     
    //ゲームオーバーになったらパネルを表示する
    void GameOver()
    {
        activeBlock.MoveUp();
        //ゲームオーバーパネルの非表示設定
        if (!gameOverPanel.activeInHierarchy)
        {
            gameOverPanel.SetActive(true);
        }
        gameOver = true;
    }
    public void Restart()
    {
        SceneManager.LoadScene(1);
    }
    public void Title()
    {
        SceneManager.LoadScene(0);
    }
}
