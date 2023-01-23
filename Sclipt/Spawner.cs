using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
   
    //配列の作成（生成するブロックすべてを格納する）
    [SerializeField]
    public Block[] Blocks;
    [SerializeField]
    public Block[] TargetBlocks;
    [SerializeField]
    public Block[] HoldBlocks;
    //関数の作成//
    public int No =0;//0以上7未満から数値が呼ばれる
    public int hold = 0;
    public int next = 0;
    public int next2 = 0;
    public bool HoldOn = default;

    
    public Block GetRandomBlock()
    {

        No++;
        next =No+1;
        next2 = next + 1;
        switch(No)
        {
            
            case 5:
                next2 = 0;

                break;

            case 6:
                next = 0;
                next2 = 1;
                break;

            case 7:
                No = 0;
                next = 1;
                next2 = 2;
                break;
        
        }
        hold = No;
 
         if (Blocks[No])
         {
           TargetBlocks[No] = TargetBlocks[No];
           return Blocks[No];
                
         }
         else
         {
           return null;
         }
       
        
    }
    //選ばれたブロックを生成する関数
    public Block SpawnBlock()
    {
        Block block = Instantiate(GetRandomBlock(),transform.position, Quaternion.identity);
        if(block)
        {

            return block;
        }
        else
        {
            return null;
        }
    }
    public Block SpawnBlockTarfet()
    {
        Block block2 = Instantiate(GetRandomBlock(), transform.position, Quaternion.identity);
        if (block2)
        {

            return block2;
        }
        else
        {
            return null;
        }
    }
}
