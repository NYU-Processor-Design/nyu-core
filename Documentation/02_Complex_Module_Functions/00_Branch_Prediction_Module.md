(Note: This document is currently incomplete)
# **I/O:**

## **Inputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```clk```|1-bit|Clock Signal|
|```rstn```|1-bit|Reset Signal|
|```branch_occr```|2-bits|Specifies if instruction is guaranteed to branch, guaranteed to not branch, or could do either|

## **Outputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```branch_taken```|1-bit|Branch Taken Signal|


# **Functionality:**

## **Registers:**
- 1-bit ```curr_pred```
- 2-bit ```incorrect_pred```

## **Branch Prediction**

### **Branch Prediction Algorithm**
- Branch Prediction will be 2-bit, where the predicted branch outcome only changes after two incorrect predictions.

