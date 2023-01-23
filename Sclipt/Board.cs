using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Board : MonoBehaviour
{
    gamemanager game;
    //2次元配列の作成//
    private Transform[,] grid;

    [SerializeField] public int StartNo =-10;
    [SerializeField] private Transform emptySprite;
    [SerializeField] private int height = 30, width = 10, header = 8;
    public bool destroy =default;

    private void Awake()
    {
        grid = new Transform[width, height];
    }
    private void Start()
    {
        game = GameObject.FindObjectOfType<gamemanager>();
        CreateBoard();
  
    }
    //ボードを生成する関数の作成
    void CreateBoard()
    {
        if(emptySprite)
        {
            for(int y= 0; y < height - header; y++)
            {
                for (int x = StartNo; x < width; x++)
                {
                    Transform clone = Instantiate(emptySprite,
                        new Vector3(x, y, 0), Quaternion.identity);

                    clone.transform.parent = transform;
                }
            }
        }
    }
    //ブロックが枠内にあるかどうか判定する関数を呼ぶ関数
    public bool CheckPosition(Block block)
    {
        foreach(Transform item in block.transform)
        {
            Vector2 pos = Rounding.Round(item.position);


            if(!BoardOutCheck((int)pos.x, (int)pos.y))
            {
                return false;
            }
            if (game.SperL == false)
            {
                 if (BlockCheck((int)pos.x, (int)pos.y,block))
                {
                    return false;
                }
            }
           
        }
        return true;
    }



    //枠内にあるのか判定する関数
    bool BoardOutCheck(int x,int y)
    {
        return (x >= 0 && x < width && y >= 0);
    }
   public bool BlockCheck(int x, int y,Block block)
    {
        //二次元配列がカラではないのはほかのブロックがある時
        //親が違うのはほかのブロックがあるとき
        return (grid[x, y] != null && grid[x, y].parent != block.transform);
    }

    //ブロックが落ちたポジションを記録する関数
    public void SaveBlockInGrid(Block block)
    {
        foreach(Transform item in block.transform)
        {
            Vector2 pos = Rounding.Round(item.position);

            grid[(int)pos.x, (int)pos.y] = item;
        }
    }
    public void ClearAllRows()
    {
            for(int y = 0; y < height; y++)
        {
            if(IsComplete(y))
            {
                ClearRow(y);

                ShifRowsDown(y +1);

                y--;
                destroy = true;
            }
        }
    }
    bool IsComplete(int y)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[x,y] == null)
            {
                return false;
            }
        }
        return true;
    }
    void ClearRow(int y)
    {
        for (int x = 0; x < width; x++)
        {
            if(grid[x,y] !=null)
            {
                Destroy(grid[x, y].gameObject);
               
            }
            grid[x, y] = null;
        }
    }
    //上にあるブロックを一段下に下げる関数
    void ShifRowsDown(int startY)
    {
        for (int y = startY; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if(grid[x,y] != null)
                {
                    grid[x, y - 1] = grid[x, y];
                    grid[x, y] = null;
                    grid[x, y - 1].position += new Vector3(0, -1, 0);
                }
            }
        }
    }

    public bool OverLimit(Block block)
    {
        foreach (Transform item in block.transform)
        {
            if(item.transform.position.y >=height - header)
            {
                return true;
            }
        }
        return false;
    }
}
